#include "pch.h"
#include "BoundingRect.h"

BoundingRect::BoundingRect(Vector2 _top_left, int _width, int _height)
{
	origin_point = _top_left;
	width = _width;
	height = _height;
}

BoundingRect::~BoundingRect()
{
}

bool BoundingRect::IsColliding(Collider * _object, Vector2 &_center)
{
	std::vector <Vector2> contact_points;

	int left = origin_point.x;
	int right = origin_point.x + width;
	int top = origin_point.y;
	int bottom = origin_point.y + height;

	for (int x = left; x < right; x++)
	{
		for (int y = top; y < bottom; y++)
		{
			if (_object->ContainsPoint(x, y))
			{
				contact_points.push_back(Vector2(x, y));
			}
		}
	}

	if (contact_points.size() == 0)
	{
		return false;
	}

	_center = contact_points[contact_points.size() / 2];
	return true;
}

bool BoundingRect::ContainsPoint(int x, int y)
{
	if (x > origin_point.x && x < origin_point.x + width
		&& y > origin_point.y && y < origin_point.y + height)
	{
		return true;
	}
	return false;
}
