#include "pch.h"
#include "Player2D.h"
#include "GameStateData.h"

Player2D::Player2D(RenderData* _RD, string _filename) : ImageGO2D(_RD, _filename)
{
	m_physics = new Physics2D(_RD, _filename);

	SetLimit(Vector2(900, 500));

	CentreOrigin();

	m_physics->SetBounce(0.3f);
	m_physics->SetGrav(1);
}

Player2D::~Player2D()
{
	delete m_physics;
}

void Player2D::Tick(GameStateData * _GSD)
{
	float move_x = m_move_speed * 
		_GSD->m_gamePadState[m_controllerID].thumbSticks.leftX;
	float move_y = 0;
	if (_GSD->m_buttonState[m_controllerID].a
		== DirectX::GamePad::ButtonStateTracker::PRESSED)
	{
		m_physics->ResetForce(Y);
		move_y = -m_jump_height;
	}

	Vector2 gamePadPush = Vector2(move_x, move_y);
	
	m_physics->AddForce(m_drive * gamePadPush);

	m_physics->MoveBoundingRect(m_pos);

//GEP:: Lets go up the inheritence and share our functionality

	m_physics->Tick(_GSD, m_pos, this);

	GameObject2D::Tick(_GSD);

//after that as updated my position let's lock it inside my limits
	if (m_pos.x < 0.0f)
	{
		m_pos.x *= -1.0f;
		m_physics->ResetForce(X);
	}
	if (m_pos.y < 0.0f)
	{
		m_pos.y *= -1.0f;
		m_physics->ResetForce(Y);
	}

	if (m_pos.x > m_limit.x)
	{
		m_pos.x = 2.0f * m_limit.x - m_pos.x;
		m_physics->ResetForce(X);
	}
	if (m_pos.y > m_limit.y)
	{
		m_pos.y = 2.0f * m_limit.y - m_pos.y;
		m_physics->ResetForce(Y);
	}
}

void Player2D::Collision(Physics2D * _collision)
{
	if (_collision->GetTag() == GameObjectTag::PLATFORM)
	{
		
		m_vel.y = m_bounciness;
	}

	//if(_collision.tag == "player")
	if (_collision->GetRectangle()->GetOriginPoint().x > m_pos.x)
	{
		m_pos.x--;
	}
	else
	{
		m_pos.x++;
	}

}
