#pragma once
#include "pch.h"
#include "Collider.h"

class BoundingRect
	: public Collider
{
public:
	BoundingRect(Vector2 _center, int _width, int _height);
	~BoundingRect();

	virtual bool IsColliding(Collider* _object, Vector2 &_center);
	virtual bool ContainsPoint(int x, int y);

protected:
	int width;
	int height;
};