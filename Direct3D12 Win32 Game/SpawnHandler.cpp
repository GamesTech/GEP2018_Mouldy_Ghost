#include "pch.h"
#include "SpawnHandler.h"
#include "Events.h"

void SpawnHander::onNotify(GameObject2D * object, Event _event)
{
	switch (_event)
	{
	case Event::OBJECT_INSTANTIATED:
	{
		_2DObjects->push_back(object);
		_physics->push_back(object->GetPhysics());
		break;
	}
	case Event::OBJECT_DESTROYED:
	{
		int i = 0;
		for (std::vector<GameObject2D*>::iterator it = _2DObjects->begin();
			it != _2DObjects->end(); it++, i++)
		{
			if (*it == object)
			{
				_2DObjects->erase(_2DObjects->begin() + i);
			}
		}
		i = 0;
		for (std::vector<Physics2D*>::iterator it = _physics->begin();
			it != _physics->end(); it++, i++)
		{
			if (*it == object->GetPhysics())
			{
				_physics->erase(_physics->begin() + i);
			}
		}
		break;
	}
	}
}