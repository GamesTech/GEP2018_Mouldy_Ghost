#include "pch.h"
#include "Physics2D.h"
#include "GameStateData.h"


Physics2D::Physics2D(RenderData* _RD, string _filename):ImageGO2D(_RD,_filename)
{
}


Physics2D::~Physics2D()
{
}

void Physics2D::ResetForce(Axis _axis)
{
	switch(_axis)
	{
	case X:
		m_vel.x = 0;
		m_acc.x = 0;
		break;
	case Y:
		m_vel.y = 0;
		m_acc.y = 0;
		break;
	case BOTH:
		m_vel.x = 0;
		m_vel.y = 0;
		m_acc.x = 0;
		m_acc.y = 0;
		break;
	default:
		break;
	}
}

//GEP:: Basic Euler Solver for point mass 
void Physics2D::Tick(GameStateData * _GSD)
{
	//VERY Basic idea of drag i.e. the faster I go the more I get pulled back
	m_acc -= m_drag * m_vel;

	Vector2 newPos = m_pos + _GSD->m_dt * m_vel;
	Vector2 newVel = m_vel + _GSD->m_dt * m_acc;

	newVel.y += m_gravity_scale * m_gravity;

	m_pos = newPos;
	m_vel = newVel;
	m_acc = Vector2::Zero;

	//check for collisions
	for (int i = 0; i < _GSD->objects_in_scene.size(); i++)
	{
		Physics2D* object = _GSD->objects_in_scene[i];
		if (object != this)
		{
			if (IsColliding(object))
			{
				Collision(object);

				bool on_list = false;
				for (int j = 0; j < currently_colliding.size(); j++)
				{
					if (currently_colliding[j] == object)
					{
						on_list = true;
					}
				}
				if (!on_list)
				{
					currently_colliding.push_back(object);
					CollisionEnter(object);
				}
			}
			else
			{
				for (int j = 0; j < currently_colliding.size(); j++)
				{
					if (currently_colliding[j] == object)
					{
						CollisionExit(currently_colliding[j]);
						currently_colliding.erase(currently_colliding.begin() + j);
					}
				}
			}
		}
	}
}

bool Physics2D::ContainsPoint(int x, int y)
{
	if (x > m_bounding_rect.top_left.x
		&& x < m_bounding_rect.top_left.x + m_bounding_rect.width
		&& y > m_bounding_rect.top_left.y
		&& y < m_bounding_rect.top_left.y + m_bounding_rect.height)
	{
		return true;
	}
	return false;
}

bool Physics2D::IsColliding(Physics2D * _object)
{
	int left = m_bounding_rect.top_left.x;
	int right = m_bounding_rect.top_left.x + m_bounding_rect.width;
	int top = m_bounding_rect.top_left.y;
	int bottom = m_bounding_rect.top_left.y + m_bounding_rect.height;

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

void Physics2D::CollisionEnter(GameObject2D * _collision)
{
}

void Physics2D::Collision(GameObject2D * _collision)
{
}

void Physics2D::CollisionExit(GameObject2D * _collision)
{
}
