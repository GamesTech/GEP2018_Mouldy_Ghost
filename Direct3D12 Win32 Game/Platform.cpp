#include "pch.h"
#include "Platform.h"


Platform::Platform(RenderData* _RD, string _filename) :Physics2D(_RD, _filename)
{
	m_gravity_scale = 0;

	tag = GameObjectTag::PLATFORM;
}

Platform::~Platform()
{
}