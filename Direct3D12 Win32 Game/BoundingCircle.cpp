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

	int left = center.x - radius;
	int right = center.x + radius;
	int top = center.y - radius;
	int bottom = center.y + radius;

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
		sqrt(pow(x - center.x, 2)
			+ pow(y - center.y, 2));

	return distance < radius;
}
