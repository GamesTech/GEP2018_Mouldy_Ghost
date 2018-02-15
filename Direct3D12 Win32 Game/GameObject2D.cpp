#include "pch.h"
#include "GameObject2D.h"


GameObject2D::GameObject2D()
{
}


GameObject2D::~GameObject2D()
{
}

void GameObject2D::SetPos(Vector2 _pos)
{
	m_pos = _pos;
}

void GameObject2D::SetOri(float _ori)
{
	m_orientation = _ori;

	
}

void GameObject2D::Tick(GameStateData * _GSD)
{
	if (m_pos != previous_pos)
	{
		Vector2 dif = m_pos - previous_pos;
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->SetPos(children[i]->GetPos() + dif);
		}
	previous_pos = m_pos;
	}

	//if (m_orientation != previous_ori)
	//{
	//	for (int i = 0; i < children.size(); i++)
	//	{
	//		children[i]->SetOri(m_orientation);

	//		children[i]->SetPos(children[i]->GetPos() + Vector2::Lerp(previous_pos, m_pos, m_orientation));

	//	}
	//	previous_ori = m_orientation;
	//}
	//

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
	
	parent->AddChild(this);
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
