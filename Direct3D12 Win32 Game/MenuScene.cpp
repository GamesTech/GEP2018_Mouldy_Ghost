#include "pch.h"
#include "MenuScene.h"
#include "RenderData.h"
#include "Events.h"
#include "Background.h"

MenuScene::MenuScene()
{
}


MenuScene::~MenuScene()
{
}

void MenuScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_testMenu->Tick(m_GSD);
}

void MenuScene::Reset()
{

}

void MenuScene::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	m_cam = new Camera(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam;
	m_3DObjects.push_back(m_cam);

	m_background = new Background(m_RD, "nige", 1);
	m_background->SetSpawn((m_GSD->window_size + Vector2(0, 100)) / 2);
	m_2DObjects.push_back(m_background);

	m_testMenu = std::make_unique<Menu>(Vector2(m_GSD->window_size.x/2 + (150), m_GSD->window_size.y/2 - 100), MenuButton(Event::CHANGE_SCENE_MELEE_MENU, _RD, "gens"), "Press A\nTo Start!");
	for (int i = 0; i < listeners.size(); i++)
	{
		m_testMenu->addListener(listeners[i]);
	}
	m_testMenu->init();
	m_2DObjects.push_back(m_testMenu.get());
}
