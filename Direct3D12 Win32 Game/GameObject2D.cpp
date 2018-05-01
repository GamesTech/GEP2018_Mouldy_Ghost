#include "pch.h"
#include "GameObject2D.h"
#include "Physics2D.h"
#include "EventHandler.h"


GameObject2D::GameObject2D()
{
}


GameObject2D::~GameObject2D()
{
}

void GameObject2D::SetSpawn(Vector2 _pos)
{
	m_spawn_pos = _pos;
	ResetPos();
}

void GameObject2D::SetPos(Vector2 _pos)
{
	m_pos = _pos;
}

void GameObject2D::ResetPos()
{
	if (parent == nullptr)
	{
		m_pos = m_spawn_pos;
	}
	if (m_physics)
	{
		m_physics->ResetForce(BOTH_AXES);
	}
}

void GameObject2D::SetOri(float _ori)
{
	m_orientation = _ori;	
}

void GameObject2D::move(Vector2 _move_by)
{
	m_pos += _move_by;
}

void GameObject2D::Tick(GameStateData * _GSD)
{
	if (m_pos != previous_pos)
	{
		Vector2 dif = m_pos - previous_pos;
		dif /= 2;
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->SetPos(children[i]->GetPos() + dif);
		}
		previous_pos = m_pos;
	}
}

void GameObject2D::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom)
{
}

std::string GameObject2D::GetName()
{
	return name;
}

void GameObject2D::SetName(std::string string)
{
	name = string;
}

GameObjectTag GameObject2D::GetTag()
{
	if(this)
	return tag;
}

void GameObject2D::SetTag(GameObjectTag tag_)
{
	tag = tag_;
}

GameObject2D * GameObject2D::GetParent()
{
	return parent;
}

void GameObject2D::SetParent(GameObject2D * newParent)
{
	if (parent != nullptr)
	{
		parent->RemoveChild(this);
	}

	parent = newParent;
	
	if (parent != nullptr)
	{
		parent->AddChild(this);
	}
}

void GameObject2D::AddChild(GameObject2D * object)
{
	
	children.push_back(object);
}

void GameObject2D::RemoveChild(GameObject2D * child)
{
	//yo

	for (int i = 0; i < children.size(); i++)
	{
		if(children[i] == child)
		{
			children.erase(children.begin() + i);
		}
	}
}

void GameObject2D::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
}

void GameObject2D::Collision(Physics2D * _collision)
{
}

void GameObject2D::CollisionExit(Physics2D * _collision)
{
}

void GameObject2D::addListener(EventHandler* _event)
{
	listeners.push_back(_event);
}
