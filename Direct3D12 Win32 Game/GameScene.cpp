#include "pch.h"
#include "GameScene.h"
#include "RenderData.h"
#include "GameStateData.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialise(RenderData * _RD,
	GameStateData* _GSD, int _outputWidth,
	int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	//GEP::This is where I am creating the test objects
	m_cam = new Camera(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam;
	m_3DObjects.push_back(m_cam);

	TestPBGO3D* test3d = new TestPBGO3D();
	test3d->SetScale(5.0f);
	test3d->Init();
	m_3DObjects.push_back(test3d);

	//GPGO3D* test3d2 = new GPGO3D(GP_TEAPOT);
	//test3d2->SetPos(10.0f*Vector3::Forward+5.0f*Vector3::Right+Vector3::Down);
	//test3d2->SetScale(5.0f);
	//m_3DObjects.push_back(test3d2);	

	/*ImageGO2D *test = new ImageGO2D(m_RD, "twist");
	test->SetOri(45);
	test->SetPos(Vector2(300, 300));
	test->CentreOrigin();
	m_2DObjects.push_back(test);

	test = new ImageGO2D(m_RD, "guides_logo");
	test->SetPos(Vector2(100, 100));
	test->SetScale(Vector2(1.0f, 0.5f));
	test->SetColour(Color(1, 0, 0, 1));
	m_2DObjects.push_back(test);
*/
	//Text2D * test2 = new Text2D("testing text");
	//m_2DObjects.push_back(test2);

	for (int i = 0; i < 2; i++)
	{
		Player2D* testPlay = new Player2D(m_RD, "gens");
		testPlay->SetSpawn(Vector2(i * 400, 100));
		testPlay->SetOrigin(Vector2(100, 100));
		testPlay->SetControllerID(i);
		testPlay->SetDrive(100.0f);
		testPlay->SetMoveSpeed(3 - (1 * i));
		testPlay->SetJumpHeight(200 + (200 * i));
		
		testPlay->GetPhysics()->SetDrag(0.5f);
		testPlay->GetPhysics()->SetMass(1 + i);
		testPlay->GetPhysics()->SetBounce(0.4f);

		
		float x_size = testPlay->TextureSize().x;
		(testPlay->GetPos(), testPlay->TextureSize().x, testPlay->TextureSize().y);
		/*test->SetParent(testPlay);*/
		float y_size = testPlay->TextureSize().y;
		BoundingRect* rect = new BoundingRect(testPlay->GetPos(), x_size, y_size);

		testPlay->GetPhysics()->SetBoundingRect(rect);

		m_2DObjects.push_back(testPlay);
		m_GSD->objects_in_scene.push_back(testPlay->GetPhysics());


	}

	Platform* testplatform = new Platform(m_RD, "twist");
	testplatform->SetPos(Vector2(200, 400));
	testplatform->CentreOrigin();

	BoundingRect* rect = new BoundingRect
	(testplatform->GetPos(), testplatform->TextureSize().x, testplatform->TextureSize().y);
	
	testplatform->GetPhysics()->GetDrag();
	m_2DObjects.push_back(testplatform);

	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		for (int j = 0; j < listeners.size(); j++)
		{
			m_2DObjects[i]->addListener(listeners[j]);
		}
	}

	//SDKMeshGO3D *test3 = new SDKMeshGO3D(m_RD, "cup");
	//test3->SetPos(12.0f*Vector3::Forward + 5.0f*Vector3::Left + Vector3::Down);
	//test3->SetScale(5.0f);
	//m_3DObjects.push_back(test3);

	//test = new ImageGO2D(m_RD, "guides_logo");
	//test->SetSpawn(Vector2(100, 100));
	//test->SetScale(Vector2(1.0f, 0.5f));
	//test->SetColour(Color(1, 0, 0, 1));

	//m_2DObjects.push_back(test);

	/*test->SetParent(m_2DObjects[0]);*/
}

void GameScene::Reset()
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

void GameScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
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

	//for (int i = 0; i < m_2DObjects.size(); i++)
	//{
	//	Vector2 temp = m_2DObjects[i]->GetOrigin();
	//	m_2DObjects[i]->SetOrigin(Vector2(0, 1000));
	//	m_2DObjects[i]->SetScale(m_2DObjects[i]->GetScale() + Vector2(0.01, 0.01));
	//	m_2DObjects[i]->SetOrigin(temp);
	//}
	//no idea if this works for zooming, will check later
	//Follow up comment: it doesn't work
}

void GameScene::Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList)
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
