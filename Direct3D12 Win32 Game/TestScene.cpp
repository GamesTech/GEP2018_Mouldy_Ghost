#include "pch.h"
#include "TestScene.h"
#include "RenderData.h"
#include "GameStateData.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialise(RenderData * _RD,
	GameStateData * _GSD, int _outputWidth,
	int _outputHeight,
	std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	//GEP::This is where I am creating the test objects
	m_cam = new Camera(static_cast<float>(_outputWidth),
		static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam;
	m_3DObjects.push_back(m_cam);

	TestPBGO3D* test3d = new TestPBGO3D();
	test3d->SetScale(5.0f);
	test3d->Init();
	m_3DObjects.push_back(test3d);

	Text2D * test2 = new Text2D("I am a test scene");
	m_2DObjects.push_back(test2);

	TestSound* TS = new TestSound(_audEngine.get(), "Explo1");
	m_sounds.push_back(TS);
}

void TestScene::Reset()
{
		for (int i = 0; i < m_GSD->objects_in_scene.size(); i++)
		{
			m_GSD->objects_in_scene[i]->ResetForce(BOTH);
		}
		for (int i = 0; i < m_2DObjects.size(); i++)
		{
			m_2DObjects[i]->ResetPos();
		}

		for (int i = 0; i < m_3DObjects.size(); i++)
		{
			m_3DObjects[i]->ResetPos();
		}
	}

void TestScene::Update(DX::StepTimer const & timer,
	std::unique_ptr<DirectX::AudioEngine>& _audEngine)
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
		for (vector<Sound *>::iterator it = m_sounds.begin(); it != m_sounds.end(); it++)
		{
			(*it)->Tick(m_GSD);
		}
	}

	//Add your game logic here.
	for (vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	{
		(*it)->Tick(m_GSD);
	}

	for (vector<GameObject2D *>::iterator it = m_2DObjects.begin(); it != m_2DObjects.end(); it++)
	{
		(*it)->Tick(m_GSD);
	}
}

void TestScene::Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList)
{
	//primative batch
	m_RD->m_effect->SetProjection(m_cam->GetProj());
	m_RD->m_effect->SetView(m_cam->GetView());
	m_RD->m_effect->Apply(_commandList.Get());
	m_RD->m_effect->EnableDefaultLighting();
	m_RD->m_batch->Begin(_commandList.Get());
	for (vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	{
		if ((*it)->GetType() == GO3D_RT_PRIM)(*it)->Render(m_RD);
	}
	m_RD->m_batch->End();

	//Render Geometric Primitives
	m_RD->m_GPeffect->SetProjection(m_cam->GetProj());
	m_RD->m_GPeffect->SetView(m_cam->GetView());
	m_RD->m_GPeffect->Apply(_commandList.Get());
	for (vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	{
		if ((*it)->GetType() == GO3D_RT_GEOP)(*it)->Render(m_RD);
	}

	//Render VBO Models	
	for (vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	{
		if ((*it)->GetType() == GO3D_RT_SDK)(*it)->Render(m_RD);
	}

	//finally draw all 2D objects
	ID3D12DescriptorHeap* heaps[] = { m_RD->m_resourceDescriptors->Heap() };
	_commandList->SetDescriptorHeaps(_countof(heaps), heaps);
	m_RD->m_spriteBatch->Begin(_commandList.Get());

	for (vector<GameObject2D *>::iterator it = m_2DObjects.begin(); it != m_2DObjects.end(); it++)
	{
		(*it)->Render(m_RD);
	}

	m_RD->m_spriteBatch->End();
}
