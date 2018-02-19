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