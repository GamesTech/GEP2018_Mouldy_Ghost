#include "pch.h"
#include "GameSettingsScene.h"
#include "GameSettingsHandler.h"
#include "RenderData.h"
#include <fstream>

std::string GameSettingsScene::getFileData(std::ifstream & _file)
{
	int tries = 0;
	char c;
	//look through the file until a '>' is reached
	do
	{
		c = _file.get();
		tries++;
		assert(tries < 10000);	//breaks here if it gets stuck in the file
	} while (c != '>');

	//add the rest of the line to the data
	std::string ret_str = "";
	while (true)
	{
		c = _file.get();
		if (c != '\n' && !_file.eof())
		{
			ret_str += c;
		}
		else
		{
			break;
		}
	}

	//return the data
	return ret_str;
}


GameSettingsScene::GameSettingsScene()
{
}


GameSettingsScene::~GameSettingsScene()
{
}

void GameSettingsScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_idleHandler.update(timer, Event::CHANGE_SCENE_MAIN_MENU,
		m_input_received, &listeners);
	for (int i = 0; i < 4; i++)
	{
		if (m_GSD->menu_action[i] != MenuAction::NONE)
		{
			m_input_received = true;
		}
	}

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

			std::vector<bool> tmpvector = temp->GetAvailableItems();

			for (int i = 0; i < tmpvector.size(); i++)
			{
				if (tmpvector[i])
				{
					item_indications[i]->SetText("1");
				}
				else
				{
					item_indications[i]->SetText("0");
				}
			}
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
	m_cam = std::make_unique<Camera>(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam.get();
	m_3DObjects.push_back(m_cam.get());

	m_settingsMenu = std::make_unique<Menu>((m_GSD->window_size / 8), MenuButton
		(Event::GAME_SETTINGS_DECREASE_LIVES,
			Event::GAME_SETTINGS_INCREASE_LIVES, _RD, "gens"), "Lives: ");
	m_settingsMenu->setButtonSpace(50);
	for (int i = 0; i < listeners.size(); i++)
	{
		m_settingsMenu->addListener(listeners[i]);
	}

	m_settingsMenu->init();
	m_2DObjects.push_back(m_settingsMenu.get());
	m_settingsMenu->addButton(MenuButton(Event::GAME_SETTINGS_DECREASE_TIME, Event::GAME_SETTINGS_INCREASE_TIME, _RD, "gens"), "Time: ");
	m_settingsMenu->addButton(MenuButton(Event::CHANGE_SCENE_MELEE_MENU, _RD, "gens"), "Back");

	m_livesText = std::make_unique<Text2D>("");
	m_livesText->SetText("Test");
	m_livesText->SetPos(m_settingsMenu->getMenuButton(Event::GAME_SETTINGS_DECREASE_LIVES)->GetPos() + Vector2(220, -10));
	m_2DObjects.push_back(m_livesText.get());

	m_timeText = std::make_unique<Text2D>("");
	m_timeText->SetText("Test");
	m_timeText->SetPos(m_settingsMenu->getMenuButton(Event::GAME_SETTINGS_DECREASE_TIME)->GetPos() + Vector2(200, -10));
	m_2DObjects.push_back(m_timeText.get());

	std::ifstream all_items_file;
	all_items_file.open("..\\GameAssets\\Items\\All_Items.txt");
	int i = 0;
	m_settingsMenu->setButtonSpace(40);

	assert(all_items_file);
	while (!all_items_file.eof())
	{

		std::string item_name = getFileData(all_items_file);

		MenuButton button = MenuButton(Event::GAME_SETTINGS_ITEM_ACTIVATION, _RD, "gens");
		button.setndexToSend(i);
		button.SetScale(Vector2(0.5,0.5));
		button.getText()->SetScale(Vector2(0.5, 0.5));
		m_settingsMenu->addButton(button,item_name);
		
		
		item_indications.push_back(std::make_unique<Text2D>("1"));
		item_indications[i]->SetPos(button.GetPos() + Vector2(400, 250+i*40));
		m_2DObjects.push_back(item_indications[i].get());
		i++;
	}
	all_items_file.close();
}


