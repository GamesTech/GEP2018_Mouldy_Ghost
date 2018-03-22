#include "pch.h"
#include "GameOverScene.h"
#include "RenderData.h"

GameOverScene::GameOverScene()
{
	for (int i = 0; i < 4; i++)
	{
		m_scores[i] = new Text2D("");
	}

	m_standings.reserve(4);

	m_text_colour[0] = (Color(0.3, 0.3, 1));
	m_text_colour[1] = (Color(0, 0.7, 0));
	m_text_colour[2] = (Color(1, 0, 0));
	m_text_colour[3] = (Color(1, 1, 0));
}

GameOverScene::~GameOverScene()
{
	for (int i = 0; i < 4; i++)
	{
		if(m_scores[i])
		delete m_scores[i];
	}
}

void GameOverScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	//wait for input to return to menu
	m_goBack->Tick(m_GSD);
}

void GameOverScene::Initialise(RenderData * _RD, GameStateData * _GSD,
	int _outputWidth, int _outputHeight,
	std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	//GEP::This is where I am creating the test objects
	m_cam = new Camera(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam;
	m_3DObjects.push_back(m_cam);

	m_goBack = std::make_shared<Menu>(Vector2((m_GSD->window_size.x / 5), (m_GSD->window_size.y - 100)), MenuButton(Event::CHANGE_SCENE_CHARACTER_SELECT, m_RD, "gens"), "Back to\nCharacter Select");
	for (int i = 0; i < listeners.size(); i++)
	{
		m_goBack->addListener(listeners[i]);
	}
	m_goBack->init();
}

void GameOverScene::Reset()
{
	m_chars_in_game.clear();
}

void GameOverScene::AddCharacterToScene(Character * _c)
{
	m_chars_in_game.push_back(_c);
}

void GameOverScene::PlayerEliminated(Character * _c, int index)
{
	m_scores[m_standings.size()]->SetColour(m_text_colour[index]);

	for (int i = 0; i < m_chars_in_game.size(); i++)
	{
		if (m_chars_in_game[i] == _c)
		{
			m_standings.push_back(m_chars_in_game[i]);
		}
	}
}

void GameOverScene::SortByScores()
{
	for (int stand = 0; stand < 4; stand++)
	{
		int worst_score_so_far = 5000;
		int character_index = -1;

		for (int i = 0; i < m_chars_in_game.size(); i++)
		{
			bool character_in_array = false;

			for (int j = 0; j < m_standings.size(); j++)
			{
				if (m_standings[j] == m_chars_in_game[i])
				{
					character_in_array = true;
				}
			}

			if (m_chars_in_game[i]->GetPoints() < worst_score_so_far && !character_in_array)
			{
				worst_score_so_far = m_chars_in_game[i]->GetPoints();
				character_index = i;
			}
		}

		if (character_index != -1)
		{
			m_scores[m_standings.size()]->SetColour(m_text_colour[character_index]);
			m_standings.push_back(m_chars_in_game[character_index]);
		}
	}

	m_2DObjects.clear();
	for (int i = 0; i < m_standings.size(); i++)
	{
		Character* c = m_standings[i];
		std::string score = "#";
		score += std::to_string(m_standings.size() - i);
		score += "  ";
		score += c->GetName();
		score += "  ";
		score += std::to_string(c->GetPoints());
		m_scores[i]->SetText(score);

		int x = m_GSD->window_size.x / 2 - m_scores[i]->GetWidth(m_RD) / 2;
		int y = (m_standings.size() - i - 1) * (m_GSD->window_size.y / m_standings.size());

		m_scores[i]->SetPos(Vector2(x, y));
		m_2DObjects.push_back(m_scores[i]);
	}
	m_2DObjects.push_back(m_goBack.get());
}