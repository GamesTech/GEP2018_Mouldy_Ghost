#include "pch.h"
#include "Physics2D.h"
#include "GameStateData.h"

#if _DEBUG
#include "VisiblePhysics.h"

void Physics2D::RenderCorners()
{
	static_cast <VisiblePhysics*> (this)->Render();
}
#endif


Physics2D::Physics2D()
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

	CheckForCollisions(_GSD, _pos);
}


void Physics2D::CheckForCollisions(GameStateData * _GSD, Vector2& _pos)
{
	//check for collisions
	for (int i = 0; i < _GSD->objects_in_scene.size(); i++)
	{
		Physics2D* object = _GSD->objects_in_scene[i];
		//if the object in the list isn't this gameobject
		if (object != this)
		{
			if (m_collider.Intersects(object->GetCollider()))
			{
				Rectangle overlap = Rectangle::Intersect(m_collider, object->GetCollider());

				Vector2 normal = GetNormal(overlap.Center());
				
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

Vector2 Physics2D::GetNormal(Vector2 _point)
{
	int distances[4];
	distances[0] = abs(_point.y - m_collider.Center().y - m_collider.height / 2);
	distances[1] = abs(_point.x - m_collider.Center().x + m_collider.width / 2);
	distances[2] = abs(_point.y - m_collider.Center().y + m_collider.height / 2);
	distances[3] = abs(_point.x - m_collider.Center().x - m_collider.width / 2);
	
	int closest = 0;
	for (int i = 1; i < 4; i++)
	{
		if (distances[i] < distances[closest])
		{
			closest = i;
		}
	}

	switch (closest)
	{
	case 0:
		return Vector2(0, -1);
	case 1:
		return Vector2(1, 0);
	case 2:
		return Vector2(0, 1);
	case 3:
		return Vector2(-1, 0);
	default:
		return (Vector2(0, 0));
	}
}