#include "pch.h"
#include "SpawnHandler.h"
#include "Events.h"
#include "RenderData.h"

SpawnHandler::~SpawnHandler()
{

}

void SpawnHandler::onNotify(GameObject2D * object, Event _event)
{
	if(this)
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
		//making sure that every object that collided with the deleted one is no longer colliding with it 
		for(int i = 1; i< m_physics->size(); i ++ ) //starting with 1 because for some reason the first element is nullptr and we dont know why
		{
			(*m_physics)[i]->removeFromCurrentlyColliding(object->GetPhysics());
		}

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
