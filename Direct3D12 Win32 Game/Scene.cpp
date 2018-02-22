#include "pch.h"
#include "Scene.h"

Scene::~Scene()
{
	//delete the GO2Ds
	for (vector<GameObject2D*>::iterator it = m_2DObjects.begin(); it != m_2DObjects.end(); it++)
	{
		delete (*it);
	}
	m_2DObjects.clear();
	//delete the GO3Ds
	for (vector<GameObject3D*>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	{
		delete (*it);
	}
	m_3DObjects.clear();
	//delete the sounds
	for (vector<Sound*>::iterator it = m_sounds.begin(); it != m_sounds.end(); it++)
	{
		delete (*it);
	}
	m_sounds.clear();
}

GameObject2D * Scene::Find2DGameObjectWithName(std::string name)
{
	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		if (m_2DObjects[i]->GetName() == name)
		{
			return m_2DObjects[i];
		}
	}
}

GameObject2D** Scene::FindAll2DGameobjectsWithName(std::string name)
{
	GameObject2D** objects = nullptr;
	std::vector<int> object_indexes;
		int num = 0;

	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		if (m_2DObjects[i]->GetName() == name)
		{
			num++;
			object_indexes.push_back(i);
		}
	}

	objects = new GameObject2D*[num];

	for (int i = 0; i < object_indexes.size(); i++)
	{
		objects[i] = m_2DObjects[object_indexes[i]];
	}

	object_indexes.clear();
	return objects;
}

GameObject2D * Scene::Find2DGameObjectWithTag(GameObjectTag tag)
{
	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		if (m_2DObjects[i]->GetTag() == tag)
		{
			return m_2DObjects[i];
		}
	}

	return nullptr;
}

GameObject2D** Scene::FindAll2DGameObjectsWithTag(GameObjectTag tag)
{
	GameObject2D** objects = nullptr;
	std::vector<int> object_indexes;
		int num = 0;

	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		if (m_2DObjects[i]->GetTag() == tag)
		{
			num++;
			object_indexes.push_back(i);
		}
	}

	objects = new GameObject2D*[num];

	for (int i = 0; i < object_indexes.size(); i++)
	{
		objects[i] = m_2DObjects[object_indexes[i]];
	}

	object_indexes.clear();

	return objects;
}

void Scene::addListener(EventHandler* _event)
{
	listeners.push_back(_event);
}