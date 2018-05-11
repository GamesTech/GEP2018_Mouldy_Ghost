#pragma once
#include "ImageGO2D.h"
//GEP:: Based on the ImageGO2D a basic keyboard controlled sprite

class Cursor 
	: public ImageGO2D
{
public:

	//TODO: add a 3d player and modes to switch between different views and basic physics
	Cursor(RenderData* _RD, string _filename);
	virtual ~Cursor();

	virtual void Tick(GameStateData* _GSD);

	void SetLimit(Vector2 _lim) { m_limit = _lim; }
	Vector2 GetLimit() { return m_limit; }

protected:

	Vector2 m_limit = Vector2(800, 600);
};

