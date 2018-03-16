#include "pch.h"
#include "Platform.h"

#if _DEBUG
#include "VisiblePhysics.h"
#endif


Platform::Platform(RenderData* _RD, string _filename) :ImageGO2D(_RD, _filename)
{
#if _DEBUG
	m_physics = new VisiblePhysics(_RD);
#else
	m_physics = new Physics2D();
#endif
	m_physics->SetOwner(this);
	m_physics->SetGrav(0);

	tag = GameObjectTag::PLATFORM;
}

Platform::Platform()
{
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
	GameObject2D::Tick(_GSD);

	m_physics->Tick(_GSD, m_pos);
}

void Platform::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	if (_collision->GetOwner()->GetTag() == GameObjectTag::PLAYER)
	{
		if (_normal.y == 1)
		{
			_collision->ResetForce(Y_AXIS);
			_collision->SetGrav(0);
			_collision->GetOwner()->SetParent(this);
		}
	}
}

void Platform::Collision(Physics2D * _collision)
{}

void Platform::CollisionExit(Physics2D * _collision)
{
	if (_collision->GetOwner()->GetTag() == GameObjectTag::PLAYER)
	{
		_collision->SetGrav(1);
		_collision->GetOwner()->SetParent(nullptr);
	}
}