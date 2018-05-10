#include "pch.h"
#include "RenderData.h"
#include "GameStateData.h"
#include "Scene.h"
#include "HUD.h"
#include <fstream>

#if _DEBUG
#include "VisiblePhysics.h"
#endif

Scene::~Scene()
{
	m_2DObjects.clear();
	m_3DObjects.clear();
	m_sounds.clear();
}

std::string Scene::getFileData(std::ifstream & _file)
{
	int tries = 0;
	char c;
	//look through the file until a '>' is reached
	do
	{
		c = _file.get();
		tries++;
		assert(tries < 10000);	//breaks here if it gets stuck in the file
	} while (c != '>');

	//add the rest of the line to the data
	std::string ret_str = "";
	while (true)
	{
		c = _file.get();
		if (c != '\n' && !_file.eof())
		{
			ret_str += c;
		}
		else
		{
			break;
		}
	}

	//return the data
	return ret_str;
}

void Scene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	//this will update the audio engine but give us chance to do somehting else if that isn't working
	if (!_audEngine->Update())
	{
		if (_audEngine->IsCriticalError())
		{
			// We lost the audio device!
		}
	}
	else
	{
		//update sounds playing
		for (int i = 0; i < m_sounds.size(); i++)
		{
			(m_sounds[i])->Tick(m_GSD);
		}
	}

	//Add your game logic here.
	for (int i = 0; i < m_3DObjects.size(); i++)
	{
		(m_3DObjects[i])->Tick(m_GSD);
	}

	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		m_2DObjects[i]->Tick(m_GSD);
	}
}

void Scene::Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList)
{
	//primative batch
	m_RD->m_effect->SetProjection(m_cam->GetProj());
	m_RD->m_effect->SetView(m_cam->GetView());
	m_RD->m_effect->Apply(_commandList.Get());
	m_RD->m_effect->EnableDefaultLighting();
	m_RD->m_batch->Begin(_commandList.Get());
	for (int i = 0; i < m_3DObjects.size(); i++)
	{
		if ((m_3DObjects[i])->GetType() == GO3D_RT_PRIM)(m_3DObjects[i])->Render(m_RD);
	}
	m_RD->m_batch->End();

	//Render Geometric Primitives
	m_RD->m_GPeffect->SetProjection(m_cam->GetProj());
	m_RD->m_GPeffect->SetView(m_cam->GetView());
	m_RD->m_GPeffect->Apply(_commandList.Get());
	for (int i = 0; i < m_3DObjects.size(); i++)
	{
		if ((m_3DObjects[i])->GetType() == GO3D_RT_GEOP)(m_3DObjects[i])->Render(m_RD);
	}

	//Render VBO Models	
	for (int i = 0; i < m_3DObjects.size(); i++)
	{
		if ((m_3DObjects[i])->GetType() == GO3D_RT_SDK)(m_3DObjects[i])->Render(m_RD);
	}

	//finally draw all 2D objects
	ID3D12DescriptorHeap* heaps[] = { m_RD->m_resourceDescriptors->Heap() };
	_commandList->SetDescriptorHeaps(_countof(heaps), heaps);
	m_RD->m_spriteBatch->Begin(_commandList.Get());

	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		(m_2DObjects[i])->Render(m_RD, 0, m_cam_pos, m_cam_zoom);
#if _DEBUG
		//COMMENT OUT THIS BIT IF YOU DON'T WANNA SEE THE CORNERS ON COLLIDERS
		//if (dynamic_cast<VisiblePhysics*> ((m_2DObjects[i])->GetPhysics()))
		//{
		//	(m_2DObjects[i])->GetPhysics()->RenderCorners(m_cam_pos);
		//}
#endif
	}

	m_RD->m_spriteBatch->End();
}

void Scene::PhysicsInScene(GameStateData* _GSD)
{
	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		//check that the object isn't already in the scene
		bool in_vector = false;
		for (int j = 0; j < m_2DObjects.size(); j++)
		{
			if (m_2DObjects[j] == m_2DObjects[i])
			{
				in_vector = true;
			}
		}
		//add it and its physics to scene
		if (!in_vector)
		{
			m_2DObjects.push_back(m_2DObjects[i]);
		}
		_GSD->objects_in_scene.push_back(m_2DObjects[i]->GetPhysics());
	}
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

void Scene::setIdle(float _timer, Event _scene)
{
	m_idle_timer = _timer;
	m_idle_switch_to = _scene;
}
