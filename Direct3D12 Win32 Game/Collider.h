#pragma once

#include "pch.h"

class Collider
{
public:
	Collider() = default;
	virtual ~Collider() = default;

	virtual bool IsColliding(Collider* _object, Vector2 &_direction) = 0;
	virtual bool ContainsPoint(int x, int y) = 0;

	void SetCenter(Vector2 _origin) { center = _origin; }
	Vector2 GetCenter() { return center; }

protected:
	Vector2 center;	//top left for rects, center for circles
};