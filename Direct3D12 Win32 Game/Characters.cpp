#include "pch.h"
#include "Characters.h"
#include "GameStateData.h"
#include "RenderData.h"
#include "CharacterController.h"
#include "SpawnHandler.h"

#include "MeleeWeapon.h"

#include <jsoncons\json.hpp>
#include "Animation2D.h"

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
			if (!m_infiniteLives)
			{
				m_lives--;
			}
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

	//run->update(_GSD);
	m_physics->Tick(_GSD, m_pos);

	if (usesAnimation)
	{
		active_anim->update(_GSD);
	}

	GameObject2D::Tick(_GSD);
}

void Character::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom)
{
	Rectangle rect;
	rect = Rectangle(0, 0, m_spriteSize.x / 2, m_spriteSize.y);
	
	const RECT* r = &RECT(rect);

	Vector2 render_scale = m_scale * _zoom;

	Vector2 distance_from_origin = m_pos - _cam_pos;
	distance_from_origin *= _zoom;

	Vector2 render_pos = ((2 * _zoom) * _cam_pos) + distance_from_origin;
	render_pos.x += m_spriteSize.x / 4;

	if (usesAnimation)
	{
		active_anim->Render(_RD, _cam_pos, _zoom, render_scale, m_pos, m_resourceNum, m_colour, m_orientation, m_origin, flipped);
	}
	else
	{
		if (!flipped)
		{
			_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
				GetTextureSize(m_texture.Get()),
				render_pos, r, m_colour, m_orientation, m_origin, render_scale);
		}
		else
		{
			_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
				GetTextureSize(m_texture.Get()),
				render_pos, r, m_colour, m_orientation, m_origin, render_scale, SpriteEffects::SpriteEffects_FlipHorizontally, 0);
		}
	}
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

void Character::SetController(CharacterController * _controller)
{
	m_controller = _controller;
	switch (_controller->GetControllerID())
	{
	case 0:
		m_text_colour = (Color(0.3, 0.3, 1));
		break;
	case 1:
		m_text_colour = (Color(0, 0.7, 0));
		break;
	case 2:
		m_text_colour = (Color(1, 0, 0));
		break;
	case 3:
		m_text_colour = (Color(1, 1, 0));
		break;
	default:
		break;
	}
}

void Character::loadAnimations(std::string _file, RenderData* _RD)
{
	//load animations here
	usesAnimation = true;
	using jsoncons::json;

	std::string path = "..\\GameAssets\\Characters\\" + _file + ".json";

	std::ifstream
		is(path);

	json animations;
	is >> animations;

	Rectangle spritebox;

	for (const auto& type : animations.members())
	{
		const std::string name = type.name();
		const auto& data = type.value();

		if (name == "run")
		{
			run_anim = std::make_shared<Animation2D>(_RD, data["spritesheet"].as_string(), m_resourceNum);
			run_anim->setFramerate(data["framerate"].as_long());
			run_anim->setIncrements(Vector2 (data["xIncrements"].as_long(), data["yIncrements"].as_long()));
			spritebox = Rectangle(data["startX"].as_long(), data["startY"].as_long(), data["boxWidth"].as_long(), data["boxHeight"].as_long());
			run_anim->setSpriteBoxStartPos(Vector2(spritebox.x, spritebox.y));
			run_anim->setSpriteBox(spritebox);
			run_anim->setMaxFrames(data["frames"].as_int());
		}
		else if (name == "jump")
		{
			jump_anim = std::make_shared<Animation2D>(_RD, data["spritesheet"].as_string(), m_resourceNum);
			jump_anim->setFramerate(data["framerate"].as_long());
			jump_anim->setIncrements(Vector2(data["xIncrements"].as_long(), data["yIncrements"].as_long()));
			spritebox = Rectangle(data["startX"].as_long(), data["startY"].as_long(), data["boxWidth"].as_long(), data["boxHeight"].as_long());
			jump_anim->setSpriteBoxStartPos(Vector2(spritebox.x, spritebox.y));
			jump_anim->setSpriteBox(spritebox);
			jump_anim->setMaxFrames(data["frames"].as_int());
		}
	}

	SetSpriteSize(Vector2(spritebox.width, spritebox.height), 0);
	active_anim = run_anim.get();
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

		if (active_anim)
		{
			switchAnimation(run_anim.get());
		}
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

const Color Character::getTextColour() const
{
	return m_text_colour;
}

void Character::setTextColour(Color colour)
{
	m_text_colour = colour;
}

int Character::PlayerJump(std::vector<GameAction> _actions)
{
	if (InputSystem::searchForAction(P_JUMP, _actions) && m_dash_recover && !m_attacking)
	{
		if (m_jumps < m_jump_limit)
		{
			m_physics->ResetForce(Y_AXIS);
			m_jumps++;
			if (usesAnimation)
			{
				switchAnimation(jump_anim.get());
			}
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
			m_held_item->GetPhysics()->ResetForce(BOTH_AXES);
			m_held_item->GetPhysics()->AddForce(Vector2(50000 * m_facing, -10000));
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

		//if you are holding a weapon
		if (m_held_item && m_held_item->getitemType() == ItemType::MELEE_WEAPON)
		{
			MeleeWeaponAttack(_GSD, actions_to_check);
		}
		else //no weapon equipped
		{

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

void Character::MeleeWeaponAttack(GameStateData * _GSD, std::vector<GameAction> _actions)
{
	MeleeWeapon* tmp_melee = static_cast<MeleeWeapon*>(m_held_item);

	if (m_jumps != 0) //midair
	{

		if (!m_attacking)
		{
			if (InputSystem::searchForAction(P_RELEASE_SPECIAL, _actions)
				|| InputSystem::searchForAction(P_RELEASE_BASIC, _actions))
			{
				tmp_melee->use(this);

				if (InputSystem::searchForAction(P_CROUCH, _actions))
				{
					tmp_melee->attack(0, 4);
					m_physics->ResetForce(Y_AXIS);
					m_physics->AddForce(Vector2(0, 20000));
				}
				else if (InputSystem::searchForAction(P_HOLD_UP, _actions))
				{
					tmp_melee->attack(0, 3);
					m_physics->ResetForce(Y_AXIS);
					m_physics->AddForce(Vector2(0, -20000));
				}
				else
				{
					//facing

					if (m_facing == 1)
					{
						tmp_melee->attack(0, 1);
					}
					else
					{
						tmp_melee->attack(0, 2);
					}

				}
				m_attacking = true;
			}
		}
	}
	else
	{
		if (InputSystem::searchForAction(P_HOLD_BASIC, _actions)
		|| InputSystem::searchForAction(P_HOLD_SPECIAL, _actions))
		{
			m_charge_time += _GSD->m_dt;
			m_attacking = true;
		}
		
	

			if (InputSystem::searchForAction(P_RELEASE_SPECIAL, _actions)
				|| InputSystem::searchForAction(P_RELEASE_BASIC, _actions))
			{
				tmp_melee->use(this);
				if (m_facing == 1)
				{
					tmp_melee->attack(m_charge_time, 1);
				}
				else
				{
					tmp_melee->attack(m_charge_time, 2);
				}
				m_charge_time = 0;
			}
		
	}
	
}

void Character::switchAnimation(Animation2D * _new)
{
	_new->reset();
	active_anim = _new;
}

void Character::FlipX()
{
	flipped = !flipped;
}