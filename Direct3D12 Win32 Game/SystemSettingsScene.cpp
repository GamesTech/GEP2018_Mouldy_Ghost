#include "pch.h"
#include "SystemSettingsScene.h"
#include "AudioHandler.h"
#include "RenderData.h"

SystemSettingsScene::SystemSettingsScene()
{
}

SystemSettingsScene::~SystemSettingsScene()
{
}

void SystemSettingsScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		if (listeners[i]->getType() == "Audio")
		{
			AudioHandler* temp = static_cast<AudioHandler*>(listeners[i]);
			m_music_vol->SetText(std::to_string(temp->getMusicVol()));
			m_sound_vol->SetText(std::to_string(temp->getSoundVol()));
		}
	}

	m_settingsMenu->Tick(m_GSD);
}

void SystemSettingsScene::Reset()
{
}

void SystemSettingsScene::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	m_cam = std::make_unique<Camera>(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam.get();
	m_3DObjects.push_back(m_cam.get());

	m_settingsMenu = std::make_unique<Menu>((m_GSD->window_size / 8), 
		MenuButton(Event::CHANGE_SCENE_MELEE_MENU, _RD, "gens"), "Back");
	m_settingsMenu->setButtonSpace(50);
	for (int i = 0; i < listeners.size(); i++)
	{
		m_settingsMenu->addListener(listeners[i]);
	}

    //create the menu
	m_settingsMenu->init();
	m_2DObjects.push_back(m_settingsMenu.get());
	m_settingsMenu->addButton(MenuButton(Event::GAME_SETTINGS_DECREASE_SOUND,
		Event::GAME_SETTINGS_INCREASE_SOUND, _RD, "gens"), "Sound Volume: ");
	m_settingsMenu->addButton(MenuButton(Event::GAME_SETTINGS_DECREASE_MUSIC,
		Event::GAME_SETTINGS_INCREASE_MUSIC, _RD, "gens"), "Music Volume: ");

    //display current music volume
	m_music_vol = std::make_unique<Text2D>("");
	m_music_vol->SetText("Test");
	m_music_vol->SetPos(m_settingsMenu->getMenuButton(Event::GAME_SETTINGS_DECREASE_MUSIC)->GetPos() + Vector2(400, -10));
	m_2DObjects.push_back(m_music_vol.get());

    //display current sound volume
	m_sound_vol = std::make_unique<Text2D>("");
	m_sound_vol->SetText("Test");
	m_sound_vol->SetPos(m_settingsMenu->getMenuButton(Event::GAME_SETTINGS_DECREASE_SOUND)->GetPos() + Vector2(400, -10));
	m_2DObjects.push_back(m_sound_vol.get());
}