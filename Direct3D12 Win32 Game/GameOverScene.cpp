#include "GameOverScene.h"
#include "RenderData.h"

GameOverScene::GameOverScene()
{
	m_standings.reserve(4);

	m_text_colour[0] = (Color(0.3, 0.3, 1));
	m_text_colour[1] = (Color(0, 0.7, 0));
	m_text_colour[2] = (Color(1, 0, 0));
	m_text_colour[3] = (Color(1, 1, 0));
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	//wait for input to return to menu
}

void GameOverScene::Reset()
{
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
}

void GameOverScene::ShowStandings()
{
	for (int i = m_standings.size(); i <= 0; i--)
	{
		//render the standing
	}
}

void GameOverScene::PlayerEliminated(Character * _character)
{
	m_standings.push_back(_character);
	//set the colour
}

void GameOverScene::SortByScores(Character ** _character)
{
	for (int stand = 0; stand < 4; stand++)
	{
		int worst_score_so_far = 5000;
		int character_index = -1;

		for (int i = 0; i < 4; i++)
		{
			if (_character[i])
			{
				bool character_in_array = false;

				for (int j = 0; j < m_standings.size(); j++)
				{
					if (m_standings[j] == _character[i])
					{
						character_in_array = true;
					}
				}

				if (_character[i]->GetPoints() < worst_score_so_far && !character_in_array)
				{
					worst_score_so_far = _character[i]->GetPoints();
					character_index = i;
				}
			}
		}

		if (character_index != -1)
		{
			m_standings.push_back(_character[character_index]);
		}
	}

	//set the colour
}