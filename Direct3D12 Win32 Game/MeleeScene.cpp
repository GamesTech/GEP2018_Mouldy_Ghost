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
	m_menu->Tick(m_GSD);

	m_idleHandler.update(timer, Event::CHANGE_SCENE_MAIN_MENU,
		m_input_received, &listeners);
	for (int i = 0; i < 4; i++)
	{
		if (m_GSD->menu_action[i] != MenuAction::NONE)
		{
			m_input_received = true;
		}
	}
}

void MeleeScene::Reset()
{
}

void MeleeScene::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	//GEP::This is where I am creating the test objects
	m_cam = std::make_unique<Camera>(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam.get();
	m_3DObjects.push_back(m_cam.get());


	m_menu = std::make_unique<Menu>(Vector2(0,60), MenuButton(Event::CHANGE_SCENE_GAME_SETTINGS, _RD, "gens"), "Settings");
	for (int i = 0; i < listeners.size(); i++)
	{
		m_menu->addListener(listeners[i]);
	}
	m_menu->init();
	m_2DObjects.push_back(m_menu.get());

	//m_testParticle = std::make_unique<Particle>(Vector2(500, 500), "gens", _RD);
	//m_testParticle->setDestination(Vector2(500, 0));
	//m_testParticle->setSpeed(100);
	//m_testParticle->setLifetime(5);
	//m_2DObjects.push_back(m_testParticle.get());


	m_menu->addButton(MenuButton(Event::CHANGE_SCENE_CHARACTER_SELECT, _RD, "gens"), "Select Characters");
	//m_menu->addButton(MenuButton(Event::CHANGE_SCENE_MAIN_MENU, _RD, "gens"), "Back");
}