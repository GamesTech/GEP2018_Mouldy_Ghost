#include "pch.h"
#include "Player2D.h"
#include "GameStateData.h"
#include <algorithm>

#if _DEBUG
#include "VisiblePhysics.h"
#endif

Player2D::Player2D(RenderData* _RD, string _filename) : ImageGO2D(_RD, _filename)
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

Player2D::~Player2D()
{
	delete m_physics;
}

void Player2D::Tick(GameStateData * _GSD)
{
	Vector2 gamePadPush = Vector2(0, 0);
	if (FindInput(P_MOVE_RIGHT, _GSD))
	{
		gamePadPush.x = m_move_speed;
	}
	if (FindInput(P_MOVE_LEFT, _GSD))
	{
		gamePadPush.x = -m_move_speed;
	}
	if (FindInput(P_JUMP, _GSD))
	{
		m_physics->ResetForce(Y_AXIS);
		gamePadPush.y = -m_jump_height;
	}
	
	m_physics->AddForce(m_drive * gamePadPush);

	m_physics->MoveCollider(m_pos);

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

void Player2D::Collision(Physics2D * _collision)
{
	if (_collision->GetOwner()->GetTag() == GameObjectTag::PLATFORM)
	{
		//_collision->AddForce(Vector2(0, -_collision->GetBounce()));
		
	}

	//if(_collision.tag == "player")
	if (_collision->GetCollider().Center().x > m_pos.x)
	{
		m_pos.x--;
	}
	else
	{
		m_pos.x++;
	}

}

bool Player2D::FindInput(GameAction _action, GameStateData* _GSD)
{
	if (_GSD->game_actions[m_controllerID].size() > 0)
	{
		return std::find(_GSD->game_actions[m_controllerID].begin(),
			_GSD->game_actions[m_controllerID].end(), _action)
			!= _GSD->game_actions[m_controllerID].end();
	}
	else
	{
		return false;
	}
}