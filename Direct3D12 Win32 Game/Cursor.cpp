#include "pch.h"
#include "Cursor.h"
#include "GameStateData.h"

Cursor::Cursor(RenderData* _RD, string _filename) : ImageGO2D(_RD, _filename)
{
	m_origin = Vector2::Zero;
}


Cursor::~Cursor()
{
}

void Cursor::Tick(GameStateData * _GSD)
{
	SetPos(Vector2(m_pos.x + _GSD->m_mouseState.x, m_pos.y + _GSD->m_mouseState.y));
	if (m_pos.x > _GSD->window_size.x)
	{
		m_pos.x = _GSD->window_size.x;
	}
	if (m_pos.y > _GSD->window_size.y)
	{
		m_pos.y = _GSD->window_size.y;
	}
	if (m_pos.x < 0)
	{
		m_pos.x = 0;
	}
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
	}
}