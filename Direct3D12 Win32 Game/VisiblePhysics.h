#pragma once

#if _DEBUG

/*
Behaves the same as the physics class but the corners of the collider are rendered
*/

#include "Physics2D.h"

class RenderData;

class VisiblePhysics :
	public Physics2D
{
public:
	VisiblePhysics(RenderData* _RD);
	~VisiblePhysics();
	void Render(Vector2 _cam);

private:
	RenderData* m_RD;
	ImageGO2D* m_corners[4] = { nullptr, nullptr, nullptr, nullptr };
};
#endif