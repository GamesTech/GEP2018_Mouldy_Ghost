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

	Platform* testplatform = new Platform(m_RD, "twist");
	
	testplatform->SetPos(Vector2(400, 400));
	//testplatform->SetScale(Vector2(2, 0.2));
	//testplatform->CentreOrigin();

	Rectangle rect = Rectangle
	(testplatform->GetPos().x, testplatform->GetPos().y, 
		testplatform->TextureSize().x ,
		testplatform->TextureSize().y );
	/*testplatform->CentreOrigin();*/
	
	testplatform->GetPhysics()->SetCollider(rect);
	
	m_2DObjects.push_back(testplatform);
	m_GSD->objects_in_scene.push_back(testplatform->GetPhysics());

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