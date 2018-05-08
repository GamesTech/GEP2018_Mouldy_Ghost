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
	//find a player and get to a place where you can attack them then attack them
	for (Physics2D* object2d : _GSD->objects_in_scene)
	{
		if (object2d)
		{
			GameObject2D* owner = object2d->GetOwner();
			if (owner->GetTag() == GameObjectTag::PLAYER)
			{
				if (!m_target_player || rand() % 50 == 0)
				{
					m_target_player = owner;
				}
			}
		}
	}
	if (m_target_player)
	{
		float player_dist = getDist(m_target_player);
		if (player_dist > 100)
		{
			return moveTowards(m_target_player, _GSD);
		}
		else
		{
			GameActions actions;
			actions.push_back(GameAction::P_HOLD_BASIC);
			actions.push_back(GameAction::P_RELEASE_BASIC);
			return actions;
		}
	}
	else
	{
		state = AIState::WAITING;
		return GameActions();
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

	if (_object->GetPos().y <= m_character->GetPos().y)
	{
		if (m_character->GetPhysics()->GetVel().y > 0)
		{
			if (m_character->getActions()->canJump())
			{
				actions.push_back(GameAction::P_JUMP);
			}
			else
			{
				actions.push_back(GameAction::P_HOLD_UP);
				actions.push_back(GameAction::P_HOLD_SPECIAL);
				actions.push_back(GameAction::P_RELEASE_SPECIAL);
			}
		}
	}
	return actions;
}