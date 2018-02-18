#pragma once

#include "pch.h"

class BoundingRect
{
public:
	BoundingRect(Vector2 _top_left, int _width, int _height);
	~BoundingRect();

	bool IsColliding(BoundingRect* _object, Vector2 &_normal);
	bool ContainsPoint(int x, int y);
	void SetTopLeft(Vector2 _top_left) { top_left = _top_left; }

protected:
	int width;
	int height;
	Vector2 top_left;
	float orientation;
};