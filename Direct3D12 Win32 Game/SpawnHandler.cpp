#include "pch.h"
#include "SpawnHandler.h"
#include "Events.h"
#include "RenderData.h"

SpawnHandler::~SpawnHandler()
{
	int del_count = m_delete_queue.size();
	if (del_count)
	{
		for (int i = 0; i < del_count; i++)
		{
			if(m_delete_queue[i])
			delete m_delete_queue[i];
		}
		m_delete_queue.clear();
	}
}

void SpawnHandler::onNotify(GameObject2D * object, Event _event)
{
	switch (_event)
	{
	case Event::OBJECT_INSTANTIATED:
	{
		m_2DObjects->push_back(object);
		m_physics->push_back(object->GetPhysics());
		break;
	}
	case Event::OBJECT_DESTROYED:
	case Event::PLAYER_ELIMINATED:
	{
		m_RD->m_resourceCount--;
		int i = 0;
		for (std::vector<GameObject2D*>::iterator it = m_2DObjects->begin();
			it != m_2DObjects->end(); it++, i++)
		{
			if (*it == object)
			{
				m_2DObjects->erase(m_2DObjects->begin() + i);
				break;
			}
		}
		i = 0;
		for (std::vector<Physics2D*>::iterator it = m_physics->begin();
			it != m_physics->end(); it++, i++)
		{
			if (*it == object->GetPhysics())
			{
				m_physics->erase(m_physics->begin() + i);
				break;
			}
		}

		m_delete_queue.push_back(object);
		break;
	}
	}
}

void SpawnHandler::setData(std::vector<GameObject2D*>* _2DObjects,
	std::vector<Physics2D*>* _physics, RenderData* _RD)
{
	m_RD = _RD;
	m_2DObjects = _2DObjects;
	m_physics = _physics;
}
