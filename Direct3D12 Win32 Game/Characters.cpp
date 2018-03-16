#include "pch.h"
#include "Characters.h"
#include "GameStateData.h"
#include "CharacterController.h"

#if _DEBUG
#include "VisiblePhysics.h"
#endif

Character::Character(RenderData* _RD, string _filename, SpawnHandler* _spawner)
	: ImageGO2D(_RD, _filename)
{
	CentreOrigin();
	tag = GameObjectTag::PLAYER;
	m_spawner = _spawner;
}

Character::~Character()
{
	if (m_physics)
	{
		delete m_physics;
		m_physics = nullptr;
	}
	if (m_controller)
	{
		delete m_controller;
		m_controller = nullptr;
	}
	m_attacks.clear();
}

void Character::Tick(GameStateData * _GSD)
{
	//check death zone is accurate
	if (m_death_zone.width != _GSD->window_size.x + 800
		|| m_death_zone.height != _GSD->window_size.y + 800)
	{
		m_death_zone.width = _GSD->window_size.x + 800;
		m_death_zone.height = _GSD->window_size.y + 800;
	}

	//get input
	if (m_recovery_time <= 0)
	{
		int controller = m_controller->GetControllerID();
		GameActions actions_to_check = m_controller->GetInput(_GSD);
		Vector2 gamePadPush = Vector2(0, 0);
		gamePadPush.x = PlayerMove(actions_to_check);
		gamePadPush.y = PlayerJump(actions_to_check);
		m_physics->AddForce(gamePadPush * 100);

		PlayerAttack(_GSD);
	}
	else
	{
		m_recovery_time -= _GSD->m_dt;
	}

	if (!m_death_zone.Contains(m_pos))
	{
		//DIES
		ResetPos();
	}

//GEP:: Lets go up the inheritence and share our functionality

	m_physics->Tick(_GSD, m_pos);

	GameObject2D::Tick(_GSD);
}

void Character::CreatePhysics(RenderData* _RD)
{
#if _DEBUG
	m_physics = new VisiblePhysics(_RD);
#else
	m_physics = new Physics2D();
#endif

	m_physics->SetBounce(0.3f);
	m_physics->SetGrav(1);
	m_physics->SetOwner(this);
}

void Character::GetHit(Vector2 _dir, float _force)
{
	float knockback = _force * (m_damage + 1) / 100;
	m_physics->AddForce(_dir * knockback);
	m_recovery_time = (float)m_damage / 15.0f;
}

void Character::Collision(Physics2D * _collision)
{
	GameObjectTag o_tag = _collision->GetOwner()->GetTag();
	if (o_tag == GameObjectTag::PLATFORM)
	{
		m_jumps = 0;
	}

	if (o_tag == GameObjectTag::PLAYER)
	{
		if (_collision->GetCollider().Center().x > m_pos.x)
		{
			m_pos.x--;
		}
		else
		{
			m_pos.x++;
		}
	}
}

void Character::AddAttack(MeleeAttack _attack)
{
	MeleeAttack* a = new MeleeAttack(_attack);
	m_attacks.push_back(a);
}

int Character::PlayerJump(std::vector<GameAction> _actions)
{
	if (InputSystem::searchForAction(P_JUMP, _actions))
	{
		if (m_jumps < 1)
		{
			m_physics->ResetForce(Y_AXIS);
			m_jumps++;
			return -m_jump_height;
		}
	}
	return 0;
}

int Character::PlayerMove(std::vector<GameAction> _actions)
{
	if (InputSystem::searchForAction(P_MOVE_RIGHT, _actions))
	{
		if (m_facing == -1)
		{
			FlipX();
			m_facing = 1;
			if (parent)
			{
				m_physics->ResetForce(X_AXIS);
			}
		}
		if (parent)
		{
			return m_move_speed * 2;
		}
		return m_move_speed;
	}
	if (InputSystem::searchForAction(P_MOVE_LEFT, _actions))
	{
		if (m_facing == 1)
		{
			FlipX();
			m_facing = -1;
			if (parent)
			{
				m_physics->ResetForce(X_AXIS);
			}
		}
		if (parent)
		{
			return -m_move_speed * 2;
		}
		return -m_move_speed;
	}
	return 0;
}

void Character::PlayerAttack(GameStateData* _GSD)
{
	int controller = m_controller->GetControllerID();
	GameActions actions_to_check = m_controller->GetInput(_GSD);

	if (InputSystem::searchForAction(P_HOLD_BASIC, actions_to_check))
	{
		AttackMap attack_to_use;
		if (InputSystem::searchForAction(P_MOVE_RIGHT, actions_to_check)
			|| InputSystem::searchForAction(P_MOVE_LEFT, actions_to_check))
		{
			attack_to_use = AttackMap::SIDE_BASIC;
		}
		else if(InputSystem::searchForAction(P_CROUCH, actions_to_check))
		{
			attack_to_use = AttackMap::DOWN_BASIC;
		}
		else if (InputSystem::searchForAction(P_HOLD_UP, actions_to_check))
		{
			attack_to_use = AttackMap::UP_BASIC;
		}
		else
		{
			attack_to_use = AttackMap::BASIC_BASIC;
		}

		switch (m_attacks[attack_to_use]->GetHold())
		{
		case OnHold::HOLD_CHARGE:
			m_charging_attack = m_attacks[attack_to_use];
			m_charge_time = 0;
			m_can_attack = false;
			break;
		case OnHold::HOLD_REPEAT:
			m_spamming_attack = m_attacks[attack_to_use];
			break;
		case OnHold::HOLD_NONE:
			if (m_can_attack)
			{
				m_attacks[attack_to_use]->PerformAttack
				(m_pos, m_facing, this, _GSD, m_spawner);
				m_can_attack = false;
			}
			break;
		}
	}
	if (InputSystem::searchForAction(P_RELEASE_BASIC, actions_to_check))
	{
		if (static_cast<MeleeAttack*>(m_charging_attack))
		{
			m_charging_attack->PerformAttack
			(m_pos, m_facing, this, _GSD, m_spawner, m_charge_time);
			m_charging_attack = nullptr;
		}
		if (static_cast<MeleeAttack*>(m_spamming_attack))
		{
			m_spamming_attack = nullptr;
		}
		m_can_attack = true;
	}

	if (m_spamming_attack)
	{
		if (m_spam_cooldown >= 0)
		{
			m_spamming_attack->PerformAttack(m_pos, m_facing, this, _GSD, m_spawner);
			m_spam_cooldown = m_spamming_attack->GetDelay();
		}
		else
		{
			m_spam_cooldown += _GSD->m_dt;
		}
	}
}