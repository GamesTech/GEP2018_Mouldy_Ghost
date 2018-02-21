#include "pch.h"
#include "Physics2D.h"
#include "GameStateData.h"

Physics2D::Physics2D(RenderData* _RD, string _filename)
{

}


Physics2D::~Physics2D()
{
}

void Physics2D::ResetForce(Axis _axis)
{
	switch(_axis)
	{
	case X_AXIS:
		m_vel.x = 0;
		m_acc.x = 0;
		break;
	case Y_AXIS:
		m_vel.y = 0;
		m_acc.y = 0;
		break;
	case BOTH_AXES:
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
void Physics2D::Tick(GameStateData * _GSD, Vector2& _pos)
{
	if (m_collider.Center() != _pos)
	{
		MoveCollider(_pos - m_collider.Center());
	}

	//VERY Basic idea of drag i.e. the faster I go the more I get pulled back
	m_acc -= m_drag * m_vel;

	Vector2 newPos = _pos + _GSD->m_dt * m_vel;
	Vector2 newVel = m_vel + _GSD->m_dt * m_acc;

	newVel.y += m_gravity_scale * m_gravity;

	_pos = newPos;
	m_vel = newVel;
	m_acc = Vector2::Zero;

	//check for collisions
	for (int i = 0; i < _GSD->objects_in_scene.size(); i++)
	{
		Physics2D* object = _GSD->objects_in_scene[i];
		//if the object in the list isn't this gameobject
		if (object != this)
		{
			if (m_collider.Intersects(object->GetCollider()))
			{
				Rectangle overlap;
				overlap.Intersect(m_collider, object->GetCollider());

				Vector2 normal = overlap.Center() - m_collider.Center();
				normal.Normalize();

				owner->Collision(object);

				//check whether this object was being collided with on the last tick
				bool on_list = false;
				for (int j = 0; j < currently_colliding.size(); j++)
				{
					if (currently_colliding[j] == object)
					{
						on_list = true;
					}
				}
				//if not, call collision enter and add it to the list
				if (!on_list)
				{
					currently_colliding.push_back(object);
					owner->CollisionEnter(object, normal);
				}
			}
			else
			{
				//if the object isn't being collided with
				for (int j = 0; j < currently_colliding.size(); j++)
				{
					//check whether it was being collided with last tick
					if (currently_colliding[j] == object)
					{
						//collision exit and remove it from the list
						owner->CollisionExit(object);
						currently_colliding.erase(currently_colliding.begin() + j);
					}
				}
			}
		}
	}
}
