#include "pch.h"
#include "AIController.h"
#include "GameStateData.h"

AIController::AIController(int _controller_id)
{
	m_controllerID = _controller_id;
}

GameActions AIController::GetInput(GameStateData * _GSD)
{
	switch (state)
	{
	case AIController::AIState::WAITING:
		return waiting(_GSD);
		break;
	case AIController::AIState::FALLING:
		return falling(_GSD);
		break;
	case AIController::AIState::ATTACKING:
		return attacking(_GSD);
		break;
	default:
		break;
	}
}

GameActions AIController::falling(GameStateData * _GSD)
{
	GameObject2D* nearest_platform = nullptr;
	float platform_dist = 10000;
	for (Physics2D* object2d : _GSD->objects_in_scene)
	{
		if (object2d->GetOwner()->GetTag() == GameObjectTag::PLATFORM)
		{
			float dist = getDist(object2d->GetOwner());
			if (dist < platform_dist)
			{
				platform_dist = dist;
				nearest_platform = object2d->GetOwner();
			}
		}
	}
	if (nearest_platform)
	{
		return moveTowards(nearest_platform, _GSD);
	}
}

GameActions AIController::waiting(GameStateData * _GSD)
{
	//wait for a reason to change state
	return GameActions();
}

GameActions AIController::attacking(GameStateData * _GSD)
{
	//find the nearest player and get to a place where you can attack them then attack them
	GameObject2D* nearest_player = nullptr;
	float player_dist = 10000;
	for (Physics2D* object2d : _GSD->objects_in_scene)
	{
		if (object2d)
		{
			GameObject2D* owner = object2d->GetOwner();
			if (owner->GetTag() == GameObjectTag::PLAYER)
			{
				float dist = getDist(owner);
				if (dist < player_dist
					&& owner != m_character)
				{
					player_dist = dist;
					nearest_player = owner;
				}
			}
		}
	}
	if (nearest_player)
	{
		if (player_dist > 150)
		{
			return moveTowards(nearest_player, _GSD);
		}
		else
		{
			GameActions actions;
			if (holding != Holding::BASIC)
			{
				actions.push_back(GameAction::P_HOLD_BASIC);
				holding = Holding::BASIC;
			}
			else
			{
				actions.push_back(GameAction::P_RELEASE_BASIC);
				holding = Holding::NONE;
			}
			return actions;
		}
	}
	else
	{
		state = AIState::WAITING;
	}
}

float AIController::getDist(GameObject2D * object)
{
	Vector2 pos_a = m_character->GetPos();
	Vector2 pos_b = object->GetPos();
	Vector2 dist = pos_a - pos_b;

	return sqrt(pow(dist.x, 2) + pow(dist.y, 2));
}

GameActions AIController::moveTowards(GameObject2D * _object, GameStateData * _GSD)
{
	GameActions actions;
	if (_object->GetPos().x < m_character->GetPos().x)
	{
		actions.push_back(GameAction::P_MOVE_LEFT);
	}
	else if (_object->GetPos().x > m_character->GetPos().x)
	{
		actions.push_back(GameAction::P_MOVE_RIGHT);
	}

	if (_object->GetPos().y < m_character->GetPos().y)
	{
		if (m_character->GetPhysics()->GetVel().y > 0)
		{
			if (m_character->canJump())
			{
				actions.push_back(GameAction::P_JUMP);
			}
			else
			{
				if (holding != Holding::SPECIAL)
				{
					actions.push_back(GameAction::P_HOLD_UP);
					actions.push_back(GameAction::P_HOLD_SPECIAL);
					holding = Holding::SPECIAL;
				}
				else
				{
					actions.push_back(GameAction::P_HOLD_UP);
					actions.push_back(GameAction::P_RELEASE_SPECIAL);
					holding = Holding::NONE;
				}
			}
		}
	}
	return actions;
}