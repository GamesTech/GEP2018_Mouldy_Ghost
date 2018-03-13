#include "pch.h"

#if _DEBUG
#include "VisiblePhysics.h"
#include "RenderData.h"

VisiblePhysics::VisiblePhysics(RenderData * _RD)
{
	m_RD = _RD;

	for (int i = 0; i < 4; i++)
	{
		m_corners[i] = new ImageGO2D(m_RD, "colliderdebug");
		m_corners[i]->CentreOrigin();
	}
}

VisiblePhysics::~VisiblePhysics()
{
	if (m_corners)
	{
		for (int i = 0; i < 4; i++)
		{
			delete m_corners[i];
			m_corners[i] = nullptr;
		}
	}
}

void VisiblePhysics::Render()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_corners[i])
		{
			Vector2 corner = Vector2(m_collider.x + (m_collider.width * (i % 2))
				, m_collider.y + (m_collider.height * (i / 2)));
			m_corners[i]->SetPos(corner);
			m_corners[i]->Render(m_RD, 0);
		}
	}
}
#endif