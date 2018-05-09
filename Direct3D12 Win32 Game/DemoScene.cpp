#include "pch.h"
#include "DemoScene.h"
#include "RenderData.h"
#include "Background.h"
#include "FinalDestination.h"
#include "AIController.h"

void DemoScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	Scene::Update(timer, _audEngine);
	game_stage->update(m_GSD);

	Vector2 top_left = Vector2(100000, 100000);
	Vector2 bottom_right = Vector2(-1000, -1000);
	Vector2 avg_pos = Vector2::Zero;
	int num_players = 0;

	for (int i = 0; i < 4; i++)
	{
		if (players[i])
		{
			players[i]->SetLives(3);
			Vector2 p = players[i]->GetPos();
			avg_pos += (p * m_cam_zoom);

			top_left.x = (p.x < top_left.x) ? p.x : top_left.x;
			top_left.y = (p.y < top_left.y) ? p.y : top_left.y;

			bottom_right.x = (p.x > bottom_right.x) ? p.x : bottom_right.x;
			bottom_right.y = (p.y > bottom_right.y) ? p.y : bottom_right.y;

			num_players++;
		}
	}

	if (num_players)
	{
		avg_pos /= num_players;
		avg_pos /= m_cam_zoom;
		Vector2 mid = (m_GSD->window_size / 2) / m_cam_zoom;
		Vector2 cam_target = (avg_pos * -1) + mid;
		Vector2 dir_to_target = cam_target - m_cam_pos;
		m_cam_pos += dir_to_target / 5;

		float x_dist = top_left.x - bottom_right.x;
		float y_dist = top_left.y - bottom_right.y;
		float dist = sqrt(pow(x_dist, 2) + pow(y_dist, 2));

		m_cam_zoom = m_zoom_rate / dist;
		if (m_cam_zoom < m_min_zoom)
		{
			m_cam_zoom = m_min_zoom;
		}
		if (m_cam_zoom > m_max_zoom)
		{
			m_cam_zoom = m_max_zoom;
		}

		//this scales the zoom to the screen size
		m_cam_zoom *= (m_GSD->window_size.x / 1000);
	}

	if (!m_infiniteTime)
	{
		m_timeLeft -= timer.GetElapsedSeconds();
	}
}

void DemoScene::Initialise(RenderData * _RD, GameStateData * _GSD,
	int _outputWidth, int _outputHeight,
	std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	float w = m_GSD->window_size.x;
	float h = m_GSD->window_size.y;

	m_bg.push_back(std::make_unique<Background>(m_RD, "sky", 1));
	m_bg.back()->SetSpawn(Vector2(w * 0.4, 100));
	m_bg.push_back(std::make_unique<Background>(m_RD, "field", 1));
	m_bg.back()->SetSpawn(Vector2(w * 0.4, (h / 3) * 2));
	m_bg.push_back(std::make_unique<Background>(m_RD, "tree", 2));
	m_bg.back()->SetSpawn(Vector2(w * 0.4, h));

	for (int i = 0; i < m_bg.size(); i++)
	{
		m_bg[i]->SetScale(Vector2(w / 900, h / 600));
		m_2DObjects.push_back(m_bg[i].get());
	}

	for (int i = 0; i < listeners.size(); i++)
	{
		if (listeners[i]->getType() == "Spawn")
		{
			m_spawner = static_cast<SpawnHandler*>(listeners[i]);
		}
	}

	//give the spawner the object vectors and the render data
	m_spawner->setData(&m_2DObjects, &m_GSD->objects_in_scene, m_RD, ActiveScene::DEMO);

	//load every character into the character manager
	c_manager.PopulateCharacterList(_RD);
	item_spawner.loadAllData(_RD);

	m_cam = std::make_unique<Camera>(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam.get();
	m_3DObjects.push_back(m_cam.get());

	//creating a stage
	//could pass the name of the stage as a function paratemter
	game_stage = std::make_unique<FinalDestination>();
	game_stage->init(m_RD, m_GSD);

	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		for (int j = 0; j < listeners.size(); j++)
		{
			m_2DObjects[i]->addListener(listeners[j]);
		}
	}

	//adds all 2d objects to the stage
	game_stage->addObjectsToScene(m_2DObjects);
}