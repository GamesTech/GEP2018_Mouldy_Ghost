#include "pch.h"
#include "Player2D.h"
#include "GameStateData.h"

Player2D::Player2D(RenderData* _RD, string _filename):Physics2D(_RD,_filename)
{
	SetLimit(Vector2(1200, 700));

	CentreOrigin();

	m_bounciness = 0.3f;
	m_gravity_scale = 1;
}


Player2D::~Player2D()
{
	delete m_bounding_rect;
}

void Player2D::Tick(GameStateData * _GSD)
{
	float move_x = m_move_speed * 
		_GSD->m_gamePadState[m_controllerID].thumbSticks.leftX;
	float move_y = 0;
	if (_GSD->m_buttonState[m_controllerID].a
		== DirectX::GamePad::ButtonStateTracker::PRESSED)
	{
		ResetForce(Y);
		move_y = -m_jump_height;
	}

	Vector2 gamePadPush = Vector2(move_x, move_y);
	
	AddForce(m_drive * gamePadPush);

	m_bounding_rect->SetTopLeft(m_pos);

//GEP:: Lets go up the inheritence and share our functionality

	Physics2D::Tick(_GSD);

//after that as updated my position let's lock it inside my limits
	if (m_pos.x < 0.0f)
	{
		m_pos.x *= -1.0f;
		m_vel.x = 0;
	}
	if (m_pos.y < 0.0f)
	{
		m_pos.y *= -1.0f;
		m_vel.y = 0;
	}

	if (m_pos.x > m_limit.x)
	{
		m_pos.x = 2.0f * m_limit.x - m_pos.x;
		m_vel.x = 0;
	}
	if (m_pos.y > m_limit.y)
	{
		m_pos.y = 2.0f * m_limit.y - m_pos.y;
		m_vel.y = 0;
	}
}
