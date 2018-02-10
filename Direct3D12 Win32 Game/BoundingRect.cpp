#include "pch.h"

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
				_normal = GetCollisionNormal
				(Vector2(left, top), Vector2(right, bottom), Vector2(x, y));
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

const Vector2 BoundingRect::GetCollisionNormal
	(Vector2 top_left, Vector2 bottom_right, Vector2 contact)
	{
		Vector2 return_vector;

		int width = bottom_right.x - top_left.x;
		int height = bottom_right.y - top_left.y;

		if (contact.x < top_left.x + (width / 10))
		{
			return_vector.x = -1;
		}
		else if (contact.x > bottom_right.x - (width / 10))
		{
			return_vector.x = 1;
		}
		else
		{
			return_vector.x = 0;
		}

		if (contact.y < top_left.y + (height / 10))
		{
			return_vector.y = -1;
		}
		else if (contact.y > bottom_right.y - (height / 10))
		{
			return_vector.y = 1;
		}
		else
		{
			return_vector.y = 0;
		}

		return return_vector;
	}
