#include "pch.h"
#include "SpawnHandler.h"
#include "Events.h"
#include "RenderData.h"

SpawnHandler::SpawnHandler()
{
	m_game_data = std::make_unique<SceneData>();
	m_demo_data = std::make_unique<SceneData>();
}

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
		m_active_data->objects->push_back(object);
		m_active_data->physics->push_back(object->GetPhysics());
		break;
	}
	case Event::OBJECT_DESTROYED:
	case Event::PLAYER_ELIMINATED:
	{		
		//making sure that every object that collided with the deleted one is no longer colliding with it 
		for(int i = 1; i < m_active_data->physics->size(); i ++ ) //starting with 1 because for some reason the first element is nullptr and we dont know why
		{
			(*m_active_data->physics)[i]->removeFromCurrentlyColliding(object->GetPhysics());
		}

		int i = 0;
		for (std::vector<GameObject2D*>::iterator it = m_active_data->objects->begin();
			it != m_active_data->objects->end(); it++, i++)
		{
			if (*it == object)
			{
				m_active_data->objects->erase(m_active_data->objects->begin() + i);
				break;
			}
		}
		i = 0;
		for (std::vector<Physics2D*>::iterator it = m_active_data->physics->begin();
			it != m_active_data->physics->end(); it++, i++)
		{
			if (*it == object->GetPhysics())
			{
				m_active_data->physics->erase(m_active_data->physics->begin() + i);
				break;
			}
		}
		break;
	}
	case Event::CHANGE_SCENE_DEMO_SCREEN:
	{
		m_active_data = m_demo_data.get();
		break;
	}
	case Event::CHANGE_SCENE_GAME:
	{
		m_active_data = m_game_data.get();
		break;
	}
	}
}

void SpawnHandler::setData(std::vector<GameObject2D*>* _2DObjects,
	std::vector<Physics2D*>* _physics, RenderData* _RD, ActiveScene _scene)
{
	switch (_scene)
	{
	case ActiveScene::GAME:
		m_game_data->RD = _RD;
		m_game_data->objects = _2DObjects;
		m_game_data->physics = _physics;
		break;
	case ActiveScene::DEMO:
		m_demo_data->RD = _RD;
		m_demo_data->objects = _2DObjects;
		m_demo_data->physics = _physics;
		break;
	default:
		break;
	}
}