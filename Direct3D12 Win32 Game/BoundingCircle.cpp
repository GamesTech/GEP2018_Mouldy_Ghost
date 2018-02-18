#include "pch.h"
#include "BoundingCircle.h"

BoundingCircle::BoundingCircle(Vector2 _center, int _width, int _height)
{
}

BoundingCircle::~BoundingCircle()
{
}

bool BoundingCircle::IsColliding(Collider * _object, Vector2 & _center)
{
	std::vector <Vector2> contact_points;

	int left = origin_point.x - radius;
	int right = origin_point.x + radius;
	int top = origin_point.y - radius;
	int bottom = origin_point.y + radius;

	for (int x = left; x < right; x++)
	{
		for (int y = top; y < bottom; y++)
		{
			if (_object->ContainsPoint(x, y) && ContainsPoint(x, y))
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

bool BoundingCircle::ContainsPoint(int x, int y)
{
	float distance =
		sqrt(pow(x - origin_point.x, 2)
			+ pow(y - origin_point.y, 2));

	return distance < radius;
}
