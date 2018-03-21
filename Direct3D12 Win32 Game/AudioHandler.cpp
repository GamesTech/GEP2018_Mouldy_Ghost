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

	m_audEngine = std::make_unique<AudioEngine>();
	m_GSD = _GSD;

	m_theme = std::make_unique<Loop>(m_audEngine.get(), "Menu1");
	m_sounds.push_back(m_theme.get());

	m_menuOk = std::make_unique<TestSound>(m_audEngine.get(), "menu-ok");
	m_sounds.push_back(m_menuOk.get());

	m_levelMusic = std::make_unique<Loop>(m_audEngine.get(), "TempleTheme");
	m_sounds.push_back(m_levelMusic.get());

	m_playerDie = std::make_unique<TestSound>(m_audEngine.get(), "die2");
	m_sounds.push_back(m_playerDie.get());

	m_playerHit = std::make_unique<TestSound>(m_audEngine.get(), "hit1");
	m_sounds.push_back(m_playerHit.get());
}

void AudioHandler::onNotify(GameObject2D * entity, Event event_)
{
	switch (event_)
	{
	case Event::APPLICATION_LOADED:
		m_activeMusic = m_theme.get();
		m_activeMusic->Play();
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
	}
}
