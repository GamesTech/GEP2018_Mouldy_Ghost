#include "pch.h"
#include "Cursor.h"
#include "GameStateData.h"

Cursor::Cursor(RenderData* _RD, string _filename) : ImageGO2D(_RD, _filename)
{
	SetLimit(Vector2(1200, 700));
}


Cursor::~Cursor()
{
}

void Cursor::Tick(GameStateData * _GSD)
{
	SetPos(Vector2(m_pos.x + _GSD->m_mouseState.x, m_pos.y + _GSD->m_mouseState.y));
}