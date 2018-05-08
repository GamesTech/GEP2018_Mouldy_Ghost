#include "pch.h"
#include "CharacterActions.h"
#include "Animation2D.h"
#include "Throwable.h"
#include "MeleeWeapon.h"
#include <jsoncons\json.hpp>

void CharacterActions::Tick(GameStateData * _GSD, Character * _character)
{
	GameActions actions_to_check = m_controller->GetInput(_GSD);
	Vector2 gamePadPush = Vector2(0, 0);
	gamePadPush.x = PlayerMove(actions_to_check, _character);
	gamePadPush.y = PlayerJump(actions_to_check, _character);

	_character->GetPhysics()->AddForce(gamePadPush * 100);

	if (usesAnimation)
	{
		if (gamePadPush.x == 0 && on_floor && !active_anim->getPlay())
		{
			switchAnimation(idle_anim.get());
		}

		if (active_anim == attack_anim.get() && !on_floor && !active_anim->getPlay())
		{

			switchAnimation(jump_anim.get());
		}
	}

	PlayerAttack(_GSD, _character);
	PickUpItem(actions_to_check, _character);

	if (m_attacking)
	{
		m_charge_time += _GSD->m_dt;

		if (usesAnimation)
		{
			active_anim->reset();
		}
		switchAnimation(attack_anim.get());
	}

	if (usesAnimation)
	{
		active_anim->update(_GSD);
	}
}

void CharacterActions::SetController(CharacterController * _controller, Character* _character)
{
	m_controller = _controller;
	switch (_controller->GetControllerID())
	{
	case 0:
		_character->setTextColour(Color(0.3, 0.3, 1));
		break;
	case 1:
		_character->setTextColour(Color(0, 0.7, 0));
		break;
	case 2:
		_character->setTextColour(Color(1, 0, 0));
		break;
	case 3:
		_character->setTextColour(Color(1, 1, 0));
		break;
	default:
		break;
	}
}

void CharacterActions::loadAnimations(std::string _file, RenderData * _RD, Character* _character)
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

		int resource_num = _character->getResourceNum();
		if (name == "run")
		{
			run_anim = std::make_shared<Animation2D>(_RD, data["spritesheet"].as_string(), resource_num);
			run_anim->setFramerate(data["framerate"].as_long());
			run_anim->setIncrements(Vector2(data["xIncrements"].as_long(), data["yIncrements"].as_long()));
			spritebox = Rectangle(data["startX"].as_long(), data["startY"].as_long(), data["boxWidth"].as_long(), data["boxHeight"].as_long());
			run_anim->setSpriteBoxStartPos(Vector2(spritebox.x, spritebox.y));
			run_anim->setSpriteBox(spritebox);
			run_anim->setFurthestLeftPos(data["furthestLeftPos"].as_long());
			run_anim->setMaxFrames(data["frames"].as_int());
		}
		else if (name == "jump")
		{
			jump_anim = std::make_shared<Animation2D>(_RD, data["spritesheet"].as_string(), resource_num);
			jump_anim->setFramerate(data["framerate"].as_long());
			jump_anim->setIncrements(Vector2(data["xIncrements"].as_long(), data["yIncrements"].as_long()));
			spritebox = Rectangle(data["startX"].as_long(), data["startY"].as_long(), data["boxWidth"].as_long(), data["boxHeight"].as_long());
			jump_anim->setSpriteBoxStartPos(Vector2(spritebox.x, spritebox.y));
			jump_anim->setSpriteBox(spritebox);
			jump_anim->setFurthestLeftPos(data["furthestLeftPos"].as_long());
			jump_anim->setMaxFrames(data["frames"].as_int());
			jump_anim->setloop(false);
		}
		else if (name == "idle")
		{
			idle_anim = std::make_shared<Animation2D>(_RD, data["spritesheet"].as_string(), resource_num);
			idle_anim->setFramerate(data["framerate"].as_long());
			idle_anim->setIncrements(Vector2(data["xIncrements"].as_long(), data["yIncrements"].as_long()));
			spritebox = Rectangle(data["startX"].as_long(), data["startY"].as_long(), data["boxWidth"].as_long(), data["boxHeight"].as_long());
			idle_anim->setSpriteBoxStartPos(Vector2(spritebox.x, spritebox.y));
			idle_anim->setSpriteBox(spritebox);
			idle_anim->setFurthestLeftPos(data["furthestLeftPos"].as_long());
			idle_anim->setMaxFrames(data["frames"].as_int());
		}
		else if (name == "attack")
		{
			attack_anim = std::make_shared<Animation2D>(_RD, data["spritesheet"].as_string(), resource_num);
			attack_anim->setFramerate(data["framerate"].as_long());
			attack_anim->setIncrements(Vector2(data["xIncrements"].as_long(), data["yIncrements"].as_long()));
			spritebox = Rectangle(data["startX"].as_long(), data["startY"].as_long(), data["boxWidth"].as_long(), data["boxHeight"].as_long());
			attack_anim->setSpriteBoxStartPos(Vector2(spritebox.x, spritebox.y));
			attack_anim->setSpriteBox(spritebox);
			attack_anim->setFurthestLeftPos(data["furthestLeftPos"].as_long());
			attack_anim->setMaxFrames(data["frames"].as_int());
			attack_anim->setloop(false);
		}
	}

	_character->SetSpriteSize(Vector2(spritebox.width, spritebox.height), 0);
	_character->SetOrigin(Vector2(float(spritebox.x / 2), float(spritebox.y / 2)));
	switchAnimation(idle_anim.get());
}

int CharacterActions::PlayerJump(std::vector<GameAction> _actions, Character * _character)
{
	if (InputSystem::searchForAction(P_JUMP, _actions) && m_dash_recover && !m_attacking)
	{
		if (m_jumps < m_jump_limit)
		{
			_character->GetPhysics()->ResetForce(Y_AXIS);
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

void CharacterActions::PickUpItem(std::vector<GameAction> _actions, Character * _character)
{

	if (!m_attacking && m_held_item)
	{
		if (InputSystem::searchForAction(P_PICK_UP, _actions))
		{
			Throwable* tmp = static_cast<Throwable*>(m_held_item);
			tmp->Throw(_character);
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

			m_held_item = _character->GetPhysics()->GetItem();
			if (m_held_item)
			{

				m_held_item->pickUp(_character);

				if (m_held_item->getitemType() == ItemType::SINGLE_USE)
				{
					m_held_item = nullptr;
				}
			}

		}
	}

}

int CharacterActions::PlayerMove(std::vector<GameAction> _actions, Character * _character)
{
	if (!m_attacking)
	{

		if (InputSystem::searchForAction(P_MOVE_RIGHT, _actions))
		{
			if (on_floor)
			{
				switchAnimation(run_anim.get());
			}
			if (m_facing == -1)
			{
				FlipX();
				m_facing = 1;
				if (_character->GetParent())
				{
					_character->GetPhysics()->ResetForce(X_AXIS);
				}
			}
			if (_character->GetParent())
			{
				return m_move_speed * 2;
			}
			return m_move_speed;
		}
		if (InputSystem::searchForAction(P_MOVE_LEFT, _actions))
		{
			if (on_floor)
			{
				switchAnimation(run_anim.get());
			}
			if (m_facing == 1)
			{
				FlipX();
				m_facing = -1;
				if (_character->GetParent())
				{
					_character->GetPhysics()->ResetForce(X_AXIS);
				}
			}
			if (_character->GetParent())
			{
				return -m_move_speed * 2;
			}
			return -m_move_speed;
		}
	}
	return 0;
}

void CharacterActions::PlayerAttack(GameStateData* _GSD, Character * _character)
{
	SpawnHandler* spawn = _character->findSpawnHandler();
	if (m_dash_recover)
	{
		int controller = m_controller->GetControllerID();
		GameActions actions_to_check = m_controller->GetInput(_GSD);

		//if you are holding a weapon
		if (m_held_item && m_held_item->getitemType() == ItemType::MELEE_WEAPON)
		{
			MeleeWeaponAttack(_GSD, actions_to_check, _character);
		}
		else //no weapon equipped
		{

			if (InputSystem::searchForAction(P_HOLD_BASIC, actions_to_check))
			{
				MeleeAttack(_GSD, actions_to_check, _character);
			}
			if (InputSystem::searchForAction(P_HOLD_SPECIAL, actions_to_check))
			{
				SpecialAttack(_GSD, actions_to_check, _character);
			}
			if (InputSystem::searchForAction(P_RELEASE_SPECIAL, actions_to_check)
				|| InputSystem::searchForAction(P_RELEASE_BASIC, actions_to_check))
			{


				if (static_cast<StandardAttack*>(m_charging_attack))
				{
					m_charging_attack->PerformAttack
					(_character->GetPos(), m_facing, _character, _GSD, spawn, m_charge_time);
					m_charging_attack = nullptr;
				}
				if (static_cast<StandardAttack*>(m_spamming_attack))
				{
					m_spamming_attack = nullptr;
				}


				m_attacking = false;
				//switchAnimation(idle_anim.get());
			}


			if (m_spamming_attack)
			{
				if (m_spam_cooldown >= 0)
				{
					m_spamming_attack->PerformAttack(_character->GetPos(), m_facing, _character, _GSD, spawn);
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

void CharacterActions::MeleeAttack(GameStateData * _GSD, std::vector<GameAction> _actions, Character * _character)
{
	SpawnHandler* spawn = _character->findSpawnHandler();
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

		switch (_character->GetAttack(attack_to_use)->GetHold())
		{
		case OnHold::HOLD_CHARGE:
			m_charging_attack = _character->GetAttack(attack_to_use);
			m_charge_time = 0;
			break;
		case OnHold::HOLD_REPEAT:
			m_spamming_attack = _character->GetAttack(attack_to_use);
			break;
		case OnHold::HOLD_NONE:
			_character->GetAttack(attack_to_use)->PerformAttack
			(_character->GetPos(), m_facing, _character, _GSD, spawn);
			break;
		}
		m_attacking = true;
	}
}

void CharacterActions::SpecialAttack(GameStateData * _GSD, std::vector<GameAction> _actions, Character * _character)
{
	SpawnHandler* spawn = _character->findSpawnHandler();
	if (!m_attacking)
	{
		AttackMap attack_to_use;
		if (InputSystem::searchForAction(P_MOVE_RIGHT, _actions)
			|| InputSystem::searchForAction(P_MOVE_LEFT, _actions))
		{
			attack_to_use = AttackMap::SIDE_SPECIAL;
			m_attacking = true;
		}
		if (InputSystem::searchForAction(P_CROUCH, _actions))
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
		switch (_character->GetAttack(attack_to_use)->GetHold())
		{
		case OnHold::HOLD_CHARGE:
			m_charging_attack = _character->GetAttack(attack_to_use);
			m_charge_time = 0;
			break;
		case OnHold::HOLD_REPEAT:
			m_spamming_attack = _character->GetAttack(attack_to_use);
			break;
		case OnHold::HOLD_NONE:
			_character->GetAttack(attack_to_use)->PerformAttack
			(_character->GetPos(), m_facing, _character, _GSD, spawn);
			break;
		}
	}
}

void CharacterActions::MeleeWeaponAttack(GameStateData * _GSD, std::vector<GameAction> _actions, Character* _character)
{
	MeleeWeapon* tmp_melee = static_cast<MeleeWeapon*>(m_held_item);

	if (m_jumps != 0) //midair
	{

		if (!m_attacking)
		{
			if (InputSystem::searchForAction(P_RELEASE_SPECIAL, _actions)
				|| InputSystem::searchForAction(P_RELEASE_BASIC, _actions))
			{
				tmp_melee->use(_character);

				if (InputSystem::searchForAction(P_CROUCH, _actions))
				{
					tmp_melee->attack(0, 4);
					_character->GetPhysics()->ResetForce(Y_AXIS);
					_character->GetPhysics()->AddForce(Vector2(0, 20000));
				}
				else if (InputSystem::searchForAction(P_HOLD_UP, _actions))
				{
					tmp_melee->attack(0, 3);
					_character->GetPhysics()->ResetForce(Y_AXIS);
					_character->GetPhysics()->AddForce(Vector2(0, -20000));
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
			tmp_melee->use(_character);
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

void CharacterActions::platformHit()
{
	on_floor = true;
	m_jumps = 0;
	m_dash_recover = true;

	switchAnimation(idle_anim.get());
}

void CharacterActions::platformLeave()
{
	on_floor = false;
	switchAnimation(jump_anim.get());
}

void CharacterActions::switchAnimation(Animation2D * _new)
{
	if (_new && _new != active_anim)
	{
		_new->reset();
		active_anim = _new;
	}
	else
	{
		OutputDebugString(L"ANIMATION NOT INITIALISED");
	}
}

void CharacterActions::FlipX()
{
	flipped = !flipped;
}