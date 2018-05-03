#include "pch.h"
#include "TitleScene.h"
#include "RenderData.h"
#include "Events.h"
#include "Background.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_testMenu->Tick(m_GSD);

	m_idleHandler.update(timer, Event::CHANGE_SCENE_DEMO_SCREEN,
		m_input_received, &listeners);
	for (int i = 0; i < 4; i++)
	{
		if (m_GSD->menu_action[i] != MenuAction::NONE)
		{
			m_input_received = true;
		}
	}
}

void TitleScene::Reset()
{

}

void TitleScene::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	m_cam = std::make_unique<Camera>(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam.get();
	m_3DObjects.push_back(m_cam.get());

	m_background = std::make_unique<Background>(m_RD, "nige", 1);
	m_background->SetSpawn((m_GSD->window_size + Vector2(0, 100)) / 2);
	m_2DObjects.push_back(m_background.get());

	m_testMenu = std::make_unique<Menu>(Vector2(m_GSD->window_size.x/2 + (150), m_GSD->window_size.y/2 - 100), MenuButton(Event::CHANGE_SCENE_MELEE_MENU, _RD, "gens"), "Press A\nTo Start!");
	for (int i = 0; i < listeners.size(); i++)
	{
		m_testMenu->addListener(listeners[i]);
	}
	m_testMenu->init();
	m_2DObjects.push_back(m_testMenu.get());
}
