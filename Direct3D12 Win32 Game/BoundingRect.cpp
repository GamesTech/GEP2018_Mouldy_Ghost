#include "pch.h"
#include "BoundingRect.h"

BoundingRect::BoundingRect(Vector2 _center, int _width, int _height)
{
	center = _center;
	width = _width;
	height = _height;
}

BoundingRect::~BoundingRect()
{
}

bool BoundingRect::IsColliding(Collider * _object, Vector2 &_direction)
{
	std::vector <Vector2> contact_points;

	int left = center.x - (width / 2);
	int right = center.x + (width / 2);
	int top = center.y - (height / 2);;
	int bottom = center.y + (height / 2);

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

	Vector2 collision_center = contact_points[contact_points.size() / 2];

	Vector2 dir = center - collision_center;

	if (abs(dir.x) > abs(dir.y))
	{
		_direction.y = 0;
		_direction.x = dir.x;
	}
	else
	{
		_direction.x = 0;
		_direction.y = dir.y;
	}

	_direction.Normalize();

	return true;
}

bool BoundingRect::ContainsPoint(int x, int y)
{
	if (x > center.x - (width/2) && x < center.x + (width /2)
		&& y > center.y - (height/2) && y < center.y + (height/2))
	{
		return true;
	}
	return false;
}
