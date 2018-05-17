#pragma once
#include "EventHandler.h"
#include "Events.h"
#include "Audio.h"

class AudioHandler :
	public EventHandler
{
public:
	AudioHandler();
	~AudioHandler();

	virtual void init(GameStateData* _GSD) override;
	virtual void onNotify(GameObject2D * entity, Event event_);

	int getSoundVol();

	int getMusicVol();

	virtual std::string getType() override { return "Audio"; }

private:
	void setVol();

	float m_sound_vol = 50;
	float m_music_vol = 50;

	Loop* m_activeMusic;
	std::unique_ptr<AudioEngine> m_audEngine = nullptr;
	std::unique_ptr<Loop> m_theme = nullptr;
	std::unique_ptr<Loop> m_levelMusic = nullptr;
	std::unique_ptr<TestSound> m_menuOk = nullptr;
	std::unique_ptr<TestSound> m_playerDie = nullptr;
	std::unique_ptr<TestSound> m_playerHit = nullptr;
	std::unique_ptr<TestSound> m_settingsDemo = nullptr;

	std::vector<TestSound*> m_sounds;
	std::vector<Loop*> m_music;
};

