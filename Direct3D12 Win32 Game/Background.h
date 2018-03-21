#pragma once
#include "ImageGO2D.h"

class Background
	: public ImageGO2D
{
public:
	Background(RenderData* _RD, string _filename, int _layer);
	~Background();

	const int GetLayer() { return m_layer; }

	virtual void Tick(GameStateData* _GSD) {};
	virtual void Render(RenderData* _RD, int _sprite = 0,
		Vector2 _cam_pos = Vector2::Zero, float _zoom = 1);
private:
	int m_layer;
};