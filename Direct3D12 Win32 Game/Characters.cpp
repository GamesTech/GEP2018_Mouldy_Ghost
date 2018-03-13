#include "pch.h"
#include "Characters.h"
#include "GameStateData.h"
#include "CharacterController.h"
#include <algorithm>

#if _DEBUG
#include "VisiblePhysics.h"
#endif

Character::Character(RenderData* _RD, string _filename) : ImageGO2D(_RD, _filename)
{
#if _DEBUG
	m_physics = new VisiblePhysics(_RD);
#else
	m_physics = new Physics2D();
#endif

	SetLimit(Vector2(900, 500));

	CentreOrigin();

	m_physics->SetBounce(0.3f);
	m_physics->SetGrav(1);
	m_physics->SetOwner(this);

	tag = GameObjectTag::PLAYER;
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
	for (int i = 0; i < m_attacks.size(); i++)
	{
		if (m_attacks[i])
		{
			delete m_attacks[i];
		}
	}
	m_attacks.clear();
}

void Character::Tick(GameStateData * _GSD)
{
	int controller = m_controller->GetControllerID();
	GameActions actions_to_check = m_controller->GetInput(_GSD);
	Vector2 gamePadPush = Vector2(0, 0);
	if (InputSystem::searchForAction(P_MOVE_RIGHT, actions_to_check))
	{
		gamePadPush.x = m_move_speed;
	}
	if (InputSystem::searchForAction(P_MOVE_LEFT, actions_to_check))
	{
		gamePadPush.x = -m_move_speed;
	}
	if (InputSystem::searchForAction(P_JUMP, actions_to_check))
	{
		m_physics->ResetForce(Y_AXIS);
		gamePadPush.y = -m_jump_height;
	}
	
	m_physics->AddForce(gamePadPush * 100);
	
//GEP:: Lets go up the inheritence and share our functionality

	m_physics->Tick(_GSD, m_pos);

	GameObject2D::Tick(_GSD);

//after that as updated my position let's lock it inside my limits
	if (m_pos.x < 0.0f)
	{
		m_pos.x *= -1.0f;
		m_physics->ResetForce(X_AXIS);
	}
	if (m_pos.y < 0.0f)
	{
		m_pos.y *= -1.0f;
		m_physics->ResetForce(Y_AXIS);
	}

	if (m_pos.x > m_limit.x)
	{
		m_pos.x = 2.0f * m_limit.x - m_pos.x;
		m_physics->ResetForce(X_AXIS);
	}
	if (m_pos.y > m_limit.y)
	{
		m_pos.y = 2.0f * m_limit.y - m_pos.y;
		m_physics->ResetForce(Y_AXIS);
	}
}

void Character::GetHit(Vector2 _dir, float _force)
{
	float knockback = _force * (m_damage + 1) / 100;
	m_physics->AddForce(_dir * knockback);
}

void Character::Collision(Physics2D * _collision)
{
	GameObjectTag o_tag = _collision->GetOwner()->GetTag();
	if (o_tag == GameObjectTag::PLATFORM)
	{
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

void Character::AddAttack(Attack* _attack)
{
	m_attacks.push_back(_attack);
}
