#pragma once

#include "pch.h"

class Collider
{
public:
	Collider() = default;
	virtual ~Collider() = default;

	virtual bool IsColliding(Collider* _object, Vector2 &_center) = 0;
	virtual bool ContainsPoint(int x, int y) = 0;

	void SetOriginPoint(Vector2 _origin) { origin_point = _origin; }
	const Vector2 GetOriginPoint() { return origin_point; }

protected:
	Vector2 origin_point;	//top left for rects, center for circles
};