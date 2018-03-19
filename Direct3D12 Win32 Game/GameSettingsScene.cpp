#include "pch.h"
#include "GameSettingsScene.h"
#include "GameSettingsHandler.h"
#include "RenderData.h"


GameSettingsScene::GameSettingsScene()
{
}


GameSettingsScene::~GameSettingsScene()
{
}

void GameSettingsScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{

	for (int i = 0; i < listeners.size(); i++)
	{
		if (listeners[i]->getType() == "GameSettings")
		{
			GameSettingsHandler* temp = static_cast<GameSettingsHandler*>(listeners[i]);
			if (temp->getInfiniteLives())
			{
				m_livesText->SetText("No Limit");
			}
			else
			{
				m_livesText->SetText(std::to_string(temp->getLives()));
			}
			int tempTime = static_cast<int>(temp->getTime());
			int minutes = tempTime / 60;
			int seconds = tempTime - (minutes * 60);
			std::string timeOutput = std::to_string(minutes) + ":" + std::to_string(seconds);
			if (seconds == 0)
			{
				timeOutput += "0";
			}

			if (temp->getInfiniteTime())
			{
				timeOutput = "No Limit";
			}

			m_timeText->SetText(timeOutput);
		}
	}

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
	m_settingsMenu->addButton(MenuButton(Event::CHANGE_SCENE_MELEE_MENU, _RD, "gens"), "Back");

	m_livesText = new Text2D("");
	m_livesText->SetText("Test");
	m_livesText->SetPos(m_settingsMenu->getMenuButton(Event::GAME_SETTINGS_DECREASE_LIVES)->GetPos() + Vector2(220, -10));
	m_2DObjects.push_back(m_livesText);

	m_timeText = new Text2D("");
	m_timeText->SetText("Test");
	m_timeText->SetPos(m_settingsMenu->getMenuButton(Event::GAME_SETTINGS_DECREASE_TIME)->GetPos() + Vector2(200, -10));
	m_2DObjects.push_back(m_timeText);
}
