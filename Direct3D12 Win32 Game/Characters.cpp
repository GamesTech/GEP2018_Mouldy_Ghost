#include "pch.h"
#include "Characters.h"
#include "GameStateData.h"
#include "RenderData.h"
#include "CharacterController.h"
#include "SpawnHandler.h"
#include "Throwable.h"

#if _DEBUG
#include "VisiblePhysics.h"
#endif

Character::Character(RenderData* _RD, string _filename)
	: ImageGO2D(_RD, _filename)
{
	CentreOrigin();
	tag = GameObjectTag::PLAYER;
}

Character::~Character()
{
	m_attacks.clear();
}

void Character::Tick(GameStateData * _GSD)
{
	if (m_lives > 0)
	{
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
			PickUpItem(actions_to_check);

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
			if (m_last_to_hit)
			{
				m_last_to_hit->AddPoints(1);
			}
			m_lives--;
			m_points--;
			for (int i = 0; i < listeners.size(); i++)
			{
				listeners[i]->onNotify(this, Event::PLAYER_DEAD);
			}
			if (m_lives > 0)
			{
				ResetDamage();
				m_physics->ResetForce(BOTH_AXES);
				ResetPos();
			}
			else
			{
				for (int i = 0; i < listeners.size(); i++)
				{
					listeners[i]->onNotify(this, Event::PLAYER_ELIMINATED);
				}
			}
		}
	}

	//GEP:: Lets go up the inheritence and share our functionality

	m_physics->Tick(_GSD, m_pos);

	GameObject2D::Tick(_GSD);
}

void Character::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom)
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

	Vector2 render_scale = m_scale * _zoom;

	Vector2 distance_from_origin = m_pos - _cam_pos;
	distance_from_origin *= _zoom;

	Vector2 render_pos = ((2 * _zoom) * _cam_pos) + distance_from_origin;
	render_pos.x += m_spriteSize.x / 4;

	_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
		GetTextureSize(m_texture.Get()),
		render_pos, r, m_colour, m_orientation, m_origin, render_scale);
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

void Character::TakeDamage(int _dam)
{
	m_damage += _dam;
	m_damage = m_damage < 0 ? 0 : m_damage;
}

void Character::Hit(Vector2 _dir, float _force, Character* _attacker)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i]->onNotify(this, Event::PLAYER_HIT);
	}

	float knockback = _force * (m_damage + 1) / 100;
	m_physics->AddForce(_dir * knockback);
	m_recovery_time = 0.1f;
	m_last_to_hit = _attacker;
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

	if (o_tag == GameObjectTag::YO)
	{
		int i = 0;
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

void Character::PickUpItem(std::vector<GameAction> _actions)
{
	if (!m_attacking && m_held_item)
	{
		if (InputSystem::searchForAction(P_PICK_UP, _actions))
		{
			Throwable* tmp = static_cast<Throwable*>(m_held_item);
			tmp->Throw(this);
			m_held_item = nullptr;
			
			return;

		}
	}
	else if (!m_attacking && !m_held_item)
	{
		if (InputSystem::searchForAction(P_PICK_UP, _actions))
		{
			
			m_held_item = m_physics->GetItem();
			if (m_held_item)
			{
				m_held_item->pickUp(this);
			}
			
		}
	}
	
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
	SpawnHandler* spawn;
	for (int i = 0; i < listeners.size(); i++)
	{
		if (spawn = dynamic_cast<SpawnHandler*>(listeners[i]))
		{
			break;
		}
	}
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
				(m_pos, m_facing, this, _GSD, spawn, m_charge_time);
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
				m_spamming_attack->PerformAttack(m_pos, m_facing, this, _GSD, spawn);
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
	SpawnHandler* spawn;
	for (int i = 0; i < listeners.size(); i++)
	{
		if (spawn = dynamic_cast<SpawnHandler*>(listeners[i]))
		{
			break;
		}
	}
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
			(m_pos, m_facing, this, _GSD, spawn);
			break;
		}
		m_attacking = true;
	}
}

void Character::SpecialAttack(GameStateData * _GSD, std::vector<GameAction> _actions)
{
	SpawnHandler* spawn;
	for (int i = 0; i < listeners.size(); i++)
	{
		if (spawn = dynamic_cast<SpawnHandler*>(listeners[i]))
		{
			break;
		}
	}
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
			(m_pos, m_facing, this, _GSD, spawn);
			break;
		}
	}
}

void Character::FlipX()
{
	flipped = !flipped;
}
