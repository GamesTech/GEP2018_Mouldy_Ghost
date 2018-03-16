#include "pch.h"
#include "GameSettingsScene.h"
#include "RenderData.h"


GameSettingsScene::GameSettingsScene()
{
}


GameSettingsScene::~GameSettingsScene()
{
}

void GameSettingsScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_settingsMenu->Tick(m_GSD);
}

void GameSettingsScene::Reset()
{
}

void GameSettingsScene::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	//GEP::This is where I am creating the test objects
	m_cam = new Camera(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam;
	m_3DObjects.push_back(m_cam);

	m_settingsMenu = std::make_unique<Menu>((m_GSD->window_size / 3.5), MenuButton(Event::GAME_SETTINGS_DECREASE_LIVES,Event::GAME_SETTINGS_INCREASE_LIVES, _RD, "gens"), "Lives: ");
	for (int i = 0; i < listeners.size(); i++)
	{
		m_settingsMenu->addListener(listeners[i]);
	}
	m_settingsMenu->init();
	m_2DObjects.push_back(m_settingsMenu.get());
	m_settingsMenu->addButton(MenuButton(Event::GAME_SETTINGS_DECREASE_TIME, Event::GAME_SETTINGS_INCREASE_TIME, _RD, "gens"), "Time: ");
	m_settingsMenu->addButton(MenuButton(Event::CHANGE_SCENE_CHARACTER_SELECT, _RD, "gens"), "Back");
}
