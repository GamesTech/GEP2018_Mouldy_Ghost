#include "pch.h"
#include "GameScene.h"
#include "RenderData.h"
#include "GameStateData.h"
#include "FinalDestination.h"

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

	//creating a stage
	//could pass the name of the stage as a function paratemter
	game_stage = std::make_unique<FinalDestination>();
	game_stage->init(m_RD,m_GSD);
	


	TestPBGO3D* test3d = new TestPBGO3D();
	test3d->SetScale(5.0f);
	test3d->Init();
	m_3DObjects.push_back(test3d);

	for (int i = 0; i < 2; i++)
	{
		Player2D* testPlay = new Player2D(m_RD, "gens");
		testPlay->SetSpawn(Vector2(i * 400+400, 100));
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
		Rectangle rect = Rectangle
		(testPlay->GetPos().x, testPlay->GetPos().y, x_size, y_size);
		testPlay->GetPhysics()->SetCollider(rect);

		m_2DObjects.push_back(testPlay);
		m_GSD->objects_in_scene.push_back(testPlay->GetPhysics());
	}

	//Platform* testplatform = new Platform(_RD, "platform");

	//testplatform->SetPos(Vector2(200, 400));
	////testplatform->SetScale(Vector2(2, 0.2));
	////testplatform->CentreOrigin();

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

	///*testplatform->CentreOrigin();*/

	//testplatform->GetPhysics()->SetCollider(rect);
	//m_2DObjects.push_back(testplatform);
	////platforms.push_back(testplatform);
	//_GSD->objects_in_scene.push_back(testplatform->GetPhysics());

	
	
}

void GameScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	Scene::Update(timer, _audEngine);
	game_stage->update(m_GSD);
}

void GameScene::Reset()
{
	for (int i = 0; i < m_GSD->objects_in_scene.size(); i++)
	{
		m_GSD->objects_in_scene[i]->ResetForce(BOTH_AXES);
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



	for (vector<GameObject2D *>::iterator it = m_2DObjects.begin(); it != m_2DObjects.end(); it++)
	{
		(*it)->Tick(m_GSD);
	}

	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		Vector2 temp = m_2DObjects[i]->GetOrigin();
		m_2DObjects[i]->SetOrigin(Vector2(0, 1000));
		m_2DObjects[i]->SetScale(m_2DObjects[i]->GetScale() + Vector2(0.01, 0.01));
		m_2DObjects[i]->SetOrigin(temp);
		//convert to imageGO2D
		//get the size of the texture
		//get the current scale of the texture
		//this gives us the real size of the texture (width and height)
		//obtain the real size of the texture after scaling
		//somehow use all this information to find the point we need to transform the shape to...

		//if point was bottom left we would do: current_pos.x + difference in width, current_pos.y + difference in height
	}
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

	//Render stage
	game_stage->render(m_RD);
	

	m_RD->m_spriteBatch->End();

	
}
