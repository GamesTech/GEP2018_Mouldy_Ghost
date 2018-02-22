#include "pch.h"
#include "PhysicsScene.h"
#include "RenderData.h"
#include "GameStateData.h"
#include "TestPhys.h"

PhysicsScene::PhysicsScene()
{
}

PhysicsScene::~PhysicsScene()
{
}

void PhysicsScene::Initialise
(RenderData * _RD, GameStateData * _GSD,
	int _outputWidth, int _outputHeight,
	std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	//GEP::This is where I am creating the test objects
	m_cam = new Camera(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam;
	m_3DObjects.push_back(m_cam);

	TestPhys* phys = new TestPhys(m_RD, "rectangle");
	phys->SetSpawn(Vector2(600, 0));
	phys->SetOrigin(Vector2(100, 100));
	phys->GetPhysics()->SetDrag(0.5f);
	phys->GetPhysics()->SetBounce(40);
	int x_size = phys->TextureSize().x;
	int y_size = phys->TextureSize().y;
	Rectangle rect = Rectangle
	(phys->GetPos().x, phys->GetPos().y, x_size, y_size);
	phys->GetPhysics()->SetCollider(rect);
	m_2DObjects.push_back(phys);
	m_GSD->objects_in_scene.push_back(phys->GetPhysics());

	phys = new TestPhys(m_RD, "rectangle");
	phys->SetSpawn(Vector2(380, 400));
	phys->SetOrigin(Vector2(100, 100));
	phys->GetPhysics()->SetGrav(0);
	phys->GetPhysics()->SetBounce(0);
	x_size = phys->TextureSize().x;
	y_size = phys->TextureSize().y;
	rect = Rectangle
	(phys->GetPos().x, phys->GetPos().y, x_size, y_size);
	phys->GetPhysics()->SetCollider(rect);
	m_2DObjects.push_back(phys);
	m_GSD->objects_in_scene.push_back(phys->GetPhysics());


}

void PhysicsScene::Reset()
{
}