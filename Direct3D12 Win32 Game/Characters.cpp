#include "pch.h"
#include "Characters.h"
#include "GameStateData.h"
#include "RenderData.h"
#include "CharacterController.h"
#include "SpawnHandler.h"

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

		if (m_attacking)
		{
			m_charge_time += _GSD->m_dt;
		}
	}
	else
	{
		m_recovery_time -= _GSD->m_dt;
	}

	if (!m_death_zone.Contains(m_pos))
	{
		//DIES
		m_lives--;
		if (m_lives > 0)
		{
			ResetDamage();
			m_physics->ResetForce(BOTH_AXES);
			ResetPos();
		}
		else
		{
			m_spawner->onNotify(this, Event::OBJECT_DESTROYED);
		}
	}

//GEP:: Lets go up the inheritence and share our functionality

	m_physics->Tick(_GSD, m_pos);

	GameObject2D::Tick(_GSD);
}

void Character::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos)
{
	Rectangle rect;
	if (!flipped)
	{
		rect = Rectangle(0, 0, m_spriteSize.x / 2, m_spriteSize.y);
	}
	else
	{
		rect = Rectangle(m_spriteSize.x / 2, 0, m_spriteSize.x / 2, m_spriteSize.y);
	}
	const RECT* r = &RECT(rect);

	Vector2 render_pos = m_pos + _cam_pos;
	render_pos.x += m_spriteSize.x / 4;

	_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
		GetTextureSize(m_texture.Get()),
		render_pos, r, m_colour, m_orientation, m_origin, m_scale);
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

void Character::Hit(Vector2 _dir, float _force)
{
	float knockback = _force * (m_damage + 1) / 100;
	m_physics->AddForce(_dir * knockback);
	m_recovery_time = (float)m_damage / 15.0f;
}

void Character::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	GameObjectTag o_tag = _collision->GetOwner()->GetTag();
	if (o_tag == GameObjectTag::PLATFORM)
	{
		m_jumps = 0;
		m_dash_recover = true;
		m_last_to_hit = nullptr;
	}
	if (o_tag == GameObjectTag::ATTACK)
	{
		m_last_to_hit = static_cast<DamageCollider*>
			(_collision->GetOwner())->GetUser();
	}
}

void Character::Collision(Physics2D * _collision)
{
	GameObjectTag o_tag = _collision->GetOwner()->GetTag();
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

void Character::AddAttack(StandardAttack _attack)
{
	StandardAttack* a = new StandardAttack(_attack);
	m_attacks.push_back(a);
}

void Character::AddAttack(DashAttack _attack)
{
	DashAttack* a = new DashAttack(_attack);
	m_attacks.push_back(a);
}

int Character::PlayerJump(std::vector<GameAction> _actions)
{
	if (InputSystem::searchForAction(P_JUMP, _actions) && m_dash_recover && !m_attacking)
	{
		if (m_jumps < m_jump_limit)
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
	if (!m_attacking)
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
	}
	return 0;
}

void Character::PlayerAttack(GameStateData* _GSD)
{
	if (m_dash_recover)
	{
		int controller = m_controller->GetControllerID();
		GameActions actions_to_check = m_controller->GetInput(_GSD);

		if (InputSystem::searchForAction(P_HOLD_BASIC, actions_to_check))
		{
			MeleeAttack(_GSD, actions_to_check);
		}
		if (InputSystem::searchForAction(P_HOLD_SPECIAL, actions_to_check))
		{
			SpecialAttack(_GSD, actions_to_check);
		}
		if (InputSystem::searchForAction(P_RELEASE_SPECIAL, actions_to_check)
			|| InputSystem::searchForAction(P_RELEASE_BASIC, actions_to_check))
		{
			if (static_cast<StandardAttack*>(m_charging_attack))
			{
				m_charging_attack->PerformAttack
				(m_pos, m_facing, this, _GSD, m_spawner, m_charge_time);
				m_charging_attack = nullptr;
			}
			if (static_cast<StandardAttack*>(m_spamming_attack))
			{
				m_spamming_attack = nullptr;
			}
			m_attacking = false;
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
}

void Character::MeleeAttack(GameStateData * _GSD, std::vector<GameAction> _actions)
{
	if (!m_attacking)
	{
		AttackMap attack_to_use;
		if (InputSystem::searchForAction(P_MOVE_RIGHT, _actions)
			|| InputSystem::searchForAction(P_MOVE_LEFT, _actions))
		{
			attack_to_use = AttackMap::SIDE_BASIC;
		}
		else if (InputSystem::searchForAction(P_CROUCH, _actions))
		{
			attack_to_use = AttackMap::DOWN_BASIC;
		}
		else if (InputSystem::searchForAction(P_HOLD_UP, _actions))
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
			break;
		case OnHold::HOLD_REPEAT:
			m_spamming_attack = m_attacks[attack_to_use];
			break;
		case OnHold::HOLD_NONE:
			m_attacks[attack_to_use]->PerformAttack
			(m_pos, m_facing, this, _GSD, m_spawner);
			break;
		}
		m_attacking = true;
	}
}

void Character::SpecialAttack(GameStateData * _GSD, std::vector<GameAction> _actions)
{
	if (!m_attacking)
	{
		AttackMap attack_to_use;
		if (InputSystem::searchForAction(P_MOVE_RIGHT, _actions)
			|| InputSystem::searchForAction(P_MOVE_LEFT, _actions))
		{
			attack_to_use = AttackMap::SIDE_SPECIAL;
			m_attacking = true;
		}
		else if (InputSystem::searchForAction(P_CROUCH, _actions))
		{
			attack_to_use = AttackMap::DOWN_SPECIAL;
			m_attacking = true;
		}
		else if (InputSystem::searchForAction(P_HOLD_UP, _actions))
		{
			attack_to_use = AttackMap::UP_SPECIAL;
			m_dash_recover = false;
		}
		else
		{
			attack_to_use = AttackMap::BASIC_SPECIAL;
			m_attacking = true;
		}
		switch (m_attacks[attack_to_use]->GetHold())
		{
		case OnHold::HOLD_CHARGE:
			m_charging_attack = m_attacks[attack_to_use];
			m_charge_time = 0;
			break;
		case OnHold::HOLD_REPEAT:
			m_spamming_attack = m_attacks[attack_to_use];
			break;
		case OnHold::HOLD_NONE:
			m_attacks[attack_to_use]->PerformAttack
			(m_pos, m_facing, this, _GSD, m_spawner);
			break;
		}
	}
}

void Character::FlipX()
{
	flipped = !flipped;
}
