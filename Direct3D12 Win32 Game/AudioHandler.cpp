#include "pch.h"
#include "AudioHandler.h"


AudioHandler::AudioHandler()
{
}


AudioHandler::~AudioHandler()
{
}

void AudioHandler::init(GameStateData * _GSD)
{
	//load in our audio files on startup
	m_audEngine = std::make_unique<AudioEngine>();
	m_GSD = _GSD;

	m_theme = std::make_unique<Loop>(m_audEngine.get(), "Menu1");
	m_music.push_back(m_theme.get());

	m_menuOk = std::make_unique<TestSound>(m_audEngine.get(), "menu-ok");
	m_sounds.push_back(m_menuOk.get());

	m_levelMusic = std::make_unique<Loop>(m_audEngine.get(), "TempleTheme");
	m_music.push_back(m_levelMusic.get());

	m_playerDie = std::make_unique<TestSound>(m_audEngine.get(), "die2");
	m_sounds.push_back(m_playerDie.get());

	m_playerHit = std::make_unique<TestSound>(m_audEngine.get(), "hit1");
	m_sounds.push_back(m_playerHit.get());

	m_settingsDemo = std::make_unique<TestSound>(m_audEngine.get(), "TooSlow");
	m_sounds.push_back(m_settingsDemo.get());
}


void AudioHandler::onNotify(GameObject2D * entity, Event event_)
{
	//play sounds when things happen
	switch (event_)
	{
	case Event::GAME_SETTINGS_DECREASE_SOUND:
		if (m_sound_vol > 0)
		{
			m_sound_vol -= 0.05f;
			m_settingsDemo->Play();
			setVol();
		}
		break;
	case Event::GAME_SETTINGS_INCREASE_SOUND:
		if (m_sound_vol < 1)
		{
			m_sound_vol += 0.05f;
			m_settingsDemo->Play();
			setVol();
		}
		break;
	case Event::GAME_SETTINGS_DECREASE_MUSIC:
		if (m_music_vol > 0)
		{
			m_music_vol -= 0.05f;
			setVol();
		}
		break;
	case Event::GAME_SETTINGS_INCREASE_MUSIC:
		if (m_music_vol < 1)
		{
			m_music_vol += 0.05f;
			setVol();
		}
		break;
	case Event::APPLICATION_LOADED:
		m_activeMusic = m_theme.get();
		m_activeMusic->Play();
		setVol();
		break;
	case Event::CHANGE_SCENE_GAME:
		if (m_activeMusic != m_levelMusic.get())
		{
			m_activeMusic->Stop();
			m_activeMusic = m_levelMusic.get();
			m_activeMusic->Play();
		}
		m_menuOk->Play();
		break;
	case Event::BUTTON_PRESSED:
		m_menuOk->Play();
		break;
	case Event::PLAYER_HIT:
		m_playerHit->Play();
		break;
	case Event::PLAYER_DEAD:
		m_playerDie->Play();
		break;
	case Event::CHANGE_SCENE_MELEE_MENU:
		if (m_activeMusic != m_theme.get())
		{
			m_activeMusic->Stop();
			m_activeMusic = m_theme.get();
			m_activeMusic->Play();
		}
		break;
	case Event::QUIT_GAME:
		m_audEngine->Suspend();
		break;
	}
}

int AudioHandler::getSoundVol()
{
	return m_sound_vol * 20;
}

int AudioHandler::getMusicVol()
{
	return m_music_vol * 20;
}

void AudioHandler::setVol()
{
	for (Loop* m : m_music)
	{
		m->SetVolume(m_music_vol);
		m->Tick(m_GSD);
		if (m != m_activeMusic)
		{
			m->Stop();
		}
	}
	for (TestSound* s : m_sounds)
	{
		s->SetVolume(m_sound_vol);
	}
}