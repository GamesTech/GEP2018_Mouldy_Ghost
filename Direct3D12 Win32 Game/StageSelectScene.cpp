#include "pch.h"
#include "StageSelectScene.h"
#include "RenderData.h"
#include "GameStateData.h"
#include <fstream>
#include "GameSettingsHandler.h"
StageSelectScene::StageSelectScene()
{
}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		if (listeners[i]->getType() == "GameSettings")
		{
			GameSettingsHandler* temp = static_cast<GameSettingsHandler*>(listeners[i]);

			if (temp->isStageSelected())
			{
				for (int i = 0; i < listeners.size(); i++)
				{
					listeners[i]->onNotify(nullptr, Event::CHANGE_SCENE_GAME);
				}
			}

		}
	}

	m_StageSelectMenu->Tick(m_GSD);
}

void StageSelectScene::Reset()
{
}

void StageSelectScene::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	m_cam = std::make_unique<Camera>(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam.get();
	m_3DObjects.push_back(m_cam.get());

	m_StageSelectMenu = std::make_unique<Menu>((m_GSD->window_size / 8),
		MenuButton(Event::CHANGE_SCENE_MELEE_MENU, _RD, "gens"), "Back");
	m_StageSelectMenu->setButtonSpace(50);

	for (int i = 0; i < listeners.size(); i++)
	{
		m_StageSelectMenu->addListener(listeners[i]);
	}

	m_StageSelectMenu->init();
	m_2DObjects.push_back(m_StageSelectMenu.get());

	std::ifstream stages;
	stages.open("..\\GameAssets\\Stages\\All_Stages.txt");
	int i = 0;
	
	assert(stages);
	while (!stages.eof())
	{

		std::string stage_name = getFileData(stages);

		MenuButton button = MenuButton(Event::GAME_SETTING_STAGE_SELECT, _RD, "gens");
		button.setndexToSend(i);
		button.SetScale(Vector2(0.5, 0.5));
		button.getText()->SetScale(Vector2(0.5, 0.5));
		m_StageSelectMenu->addButton(button, stage_name);


		i++;
	}
	stages.close();

}
