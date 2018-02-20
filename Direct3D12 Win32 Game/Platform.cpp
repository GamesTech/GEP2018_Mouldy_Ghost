#include "pch.h"
#include "Platform.h"


Platform::Platform(RenderData* _RD, string _filename) :ImageGO2D(_RD, _filename)
{
	m_physics = new Physics2D(_RD, _filename);
	m_physics->SetOwner(this);
	m_physics->SetGrav(0);

	

	tag = GameObjectTag::PLATFORM;
}

Platform::~Platform()
{
	if (m_physics)
	{
		delete m_physics;
		m_physics = nullptr;
	}
}

void Platform::Tick(GameStateData * _GSD)
{
	m_physics->Tick(_GSD, m_pos);
}

void Platform::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	int i = 0;
}

void Platform::Collision(Physics2D * _collision)
{
	if (_collision->GetOwner()->GetTag() == GameObjectTag::PLAYER)
	{
		_collision->ResetForce(Y_AXIS);
	}
	/*_collision->SetBounce(m_physics->GetBounce());*/
}

void Platform::CollisionExit(Physics2D * _collision)
{
}
