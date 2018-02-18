#include "pch.h"
#include "BoundingRect.h"

BoundingRect::BoundingRect(Vector2 _top_left, int _width, int _height)
{
	top_left = _top_left;
	width = _width;
	height = _height;
}

BoundingRect::~BoundingRect()
{
}

bool BoundingRect::IsColliding(BoundingRect * _object, Vector2 &_normal)
{
	int left = top_left.x;
	int right = top_left.x + width;
	int top = top_left.y;
	int bottom = top_left.y + height;

	for (int x = left; x < right; x++)
	{
		for (int y = top; y < bottom; y++)
		{
			if (_object->ContainsPoint(x, y))
			{
				return true;
			}
		}
	}
	return false;
}

bool BoundingRect::ContainsPoint(int x, int y)
{
	if (x > top_left.x && x < top_left.x + width
		&& y > top_left.y && y < top_left.y + height)
	{
		return true;
	}
	return false;
}
