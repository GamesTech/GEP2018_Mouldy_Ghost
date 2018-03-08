#pragma once

#if _DEBUG

#include "Physics2D.h"

class RenderData;

class VisiblePhysics :
	public Physics2D
{
public:
	VisiblePhysics(RenderData* _RD);
	~VisiblePhysics();
	void Render();

private:
	RenderData* m_RD;
	ImageGO2D* m_corners[4] = { nullptr, nullptr, nullptr, nullptr };

};

#endif