#include "pch.h"
#include "MeleeScene.h"
#include "RenderData.h"


MeleeScene::MeleeScene()
{
}


MeleeScene::~MeleeScene()
{
}

void MeleeScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_testMenu->Tick(m_GSD);
	m_testParticle->Tick(m_GSD);
}

void MeleeScene::Reset()
{
}

void MeleeScene::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	//GEP::This is where I am creating the test objects
	m_cam = new Camera(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam;
	m_3DObjects.push_back(m_cam);


	m_testMenu = std::make_unique<Menu>(Vector2(0,60), MenuButton(Event::CHANGE_SCENE_GAME_SETTINGS, _RD, "gens"), "Settings");
	for (int i = 0; i < listeners.size(); i++)
	{
		m_testMenu->addListener(listeners[i]);
	}
	m_testMenu->init();
	m_2DObjects.push_back(m_testMenu.get());

	m_testParticle = std::make_unique<Particle>(Vector2(500, 500), "gens", _RD);
	m_testParticle->setDestination(Vector2(500, 0));
	m_testParticle->setSpeed(100);
	m_testParticle->setLifetime(5);
	m_2DObjects.push_back(m_testParticle.get());

	m_testMenu->addButton(MenuButton(Event::CHANGE_SCENE_CHARACTER_SELECT, _RD, "gens"), "Select Characters");
	m_testMenu->addButton(MenuButton(Event::CHANGE_SCENE_MAIN_MENU, _RD, "gens"), "Back");
}