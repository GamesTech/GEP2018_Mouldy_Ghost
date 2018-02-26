#include "pch.h"
#include "TestPhys.h"

TestPhys::TestPhys(RenderData * _RD, string _filename) :ImageGO2D(_RD, _filename)
{
	m_physics = new Physics2D();
	m_physics->SetOwner(this);
	m_physics->SetGrav(1);

	tag = GameObjectTag::YO;
}

TestPhys::~TestPhys()
{
}

void TestPhys::Tick(GameStateData * _GSD)
{
	m_physics->Tick(_GSD, m_pos);
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

	if (m_pos.x > 1100)
	{
		m_pos.x = 2.0f * 900 - m_pos.x;
		m_physics->ResetForce(X_AXIS);
	}
	if (m_pos.y > 580)
	{
		m_pos.y = 2.0f * 580 - m_pos.y;
		m_physics->ResetForce(Y_AXIS);
	}
}

void TestPhys::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	Vector2 force_to_add = (m_physics->GetBounce() * _normal) * 1000;
	m_physics->ResetForce(BOTH_AXES);
	m_physics->AddForce(force_to_add);
}

void TestPhys::Collision(Physics2D * _collision)
{
}

void TestPhys::CollisionExit(Physics2D * _collision)
{
}
