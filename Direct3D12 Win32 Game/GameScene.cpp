#include "pch.h"
#include "GameScene.h"
#include "RenderData.h"
#include "GameStateData.h"
#include "FinalDestination.h"
#include "Battlefield.h"
#include "Temple.h"
#include "CharacterController.h"
#include "GameSettingsHandler.h"
#include "Player.h"
#include "AIController.h"
#include "SpawnHandler.h"
#include "Background.h"

GameScene::GameScene()
{
    //players have colour assigned to them for their sprite and hud text
	player_tints[0] = SimpleMath::Color(0.3, 1, 1);
	player_tints[1] = SimpleMath::Color(0.3, 1, 0.3);
	player_tints[2] = SimpleMath::Color(1, 0.3, 0.3);
	player_tints[3] = SimpleMath::Color(1, 1, 0.3);

	m_2DObjects.reserve(256);
}

GameScene::~GameScene()
{
	if (m_HUD)
	{
		delete m_HUD;
		m_HUD = nullptr;
	}
}

void GameScene::Initialise(RenderData * _RD,
	GameStateData* _GSD, int _outputWidth,
	int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	
	m_RD = _RD;
	m_GSD = _GSD;

	m_HUD = new HUD(_GSD);

	float w = m_GSD->window_size.x;
	float h = m_GSD->window_size.y;

	//set background
	m_bg.push_back(std::make_unique<Background>(m_RD, "sky", -1));
	m_bg.back()->SetSpawn(Vector2(w * 0.4, 100));
	m_bg.push_back(std::make_unique<Background>(m_RD, "field", -1));
	m_bg.back()->SetSpawn(Vector2(w * 0.4, (h /3) * 2));
	m_bg.push_back(std::make_unique<Background>(m_RD, "tree", 0.7f));
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
	m_spawner->setData(&m_2DObjects, &m_GSD->objects_in_scene, m_RD, ActiveScene::GAME);

	item_spawner = ItemSpawner(m_spawner);

	//load every character into the character manager
	c_manager.PopulateCharacterList(_RD);

	std::vector<bool> tmp_available_items;

	item_spawner.loadAllData(_RD);

	stage_manager.loadAllStages(_RD);

	m_cam = std::make_unique<Camera>(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam.get();
	m_3DObjects.push_back(m_cam.get());

	//creating a stage
	//could pass the name of the stage as a function paratemter

	//allstages.push_back(std::make_unique<FinalDestination>());
	//allstages.push_back(std::make_unique<Temple>());
	//allstages.push_back(std::make_unique<Battlefield>());

	//allstages[0]->init(m_RD, m_GSD);
	//allstages[1]->init(m_RD, m_GSD);
	//allstages[2]->init(m_RD, m_GSD);


	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		for (int j = 0; j < listeners.size(); j++)
		{
			m_2DObjects[i]->addListener(listeners[j]);
		}
	}




	m_HUD->attachTimerPointer(&m_timeLeft);

	m_pause_text = std::make_unique<Text2D>("PAUSED");
	m_pause_text->SetPos(Vector2(m_GSD->window_size.x / 2, m_GSD->window_size.y / 2));
}

void GameScene::AddCharacter(int i, std::string _character, bool ai_controlled, bool demo)
{
	if (ai_controlled)
	{
		entities[i] = std::make_unique<AIController>(i);
	}
	else
	{
		entities[i] = std::make_unique<Player>(i);
	}

	//make a character for the scene
	players[i] = std::make_unique<Character>(c_manager.GetCharacter(_character));

	//colour the player
	players[i]->SetColour(player_tints[i]);
	//give the player physics
	players[i]->CreatePhysics(m_RD);
	//give the player lives
	players[i]->SetLives(m_maxLives);
	players[i]->setinfinitelives(m_infiniteLives);
	players[i]->GetPhysics()->SetDrag(0.5f);
	players[i]->GetPhysics()->SetBounce(0.4f);
	
	if (demo)
	{
		for (int j = 0; j < 4; j++)
		{
			if (players[j] != nullptr)
			{
				players[j]->SetSpawn(game_stage->getSpawn(j));
			}
		}
	}

	//give the player a collider
	float width = players[i]->TextureSize().x;
	float height = players[i]->TextureSize().y;
	Rectangle rect = Rectangle
	(players[i]->GetPos().x, players[i]->GetPos().y, width, height);
	players[i]->GetPhysics()->SetCollider(rect);

	//add the player to the scene and the hud
	m_2DObjects.push_back(players[i].get());
	m_GSD->objects_in_scene.push_back(players[i]->GetPhysics());
	entities[i]->SetCharacter(players[i].get());

	if (m_HUD)
	{
		m_HUD->AddCharacter(players[i].get());
	}

	//notify the listeners that a player is spawning in
	for (int j = 0; j < listeners.size(); j++)
	{
		players[i]->addListener(listeners[j]);
		if (!demo)
		{
			listeners[j]->onNotify(players[i].get(), Event::PLAYER_SPAWN);
		}
	}
}

void GameScene::RemoveAllCharacters()
{
	for (int i = 0; i < 4; i++)
	{
		if (players[i] != nullptr)
		{
			RemoveCharacter(players[i].get());
		}
	}
}

void GameScene::RemoveCharacter(Character* _char)
{
	//search for and remove the character from the list
	if (_char)
	{
		_char->SetLives(0);
		m_HUD->RemoveCharacter(_char);
		for (int i = 0; i < m_2DObjects.size(); i++)
		{
			if (m_2DObjects[i] == _char)
			{
				m_2DObjects.erase(m_2DObjects.begin() + i);
			}
		}

		for (int i = 0; i < m_GSD->objects_in_scene.size(); i++)
		{
			if (m_GSD->objects_in_scene[i] == _char->GetPhysics())
			{
				m_GSD->objects_in_scene.erase(m_GSD->objects_in_scene.begin() + i);
			}
		}
	}
}

void GameScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	for (int i = 0; i < 4; i++)
	{
		if (InputSystem::searchForAction(GameAction::P_PAUSE, m_GSD->game_actions[i]))
		{
			paused = !paused;
		}
	}

	if (m_game_over_check != GameOverCheck::FREEZE)
	{
		if (!paused)
		{
			Scene::Update(timer, _audEngine);
			game_stage->update(m_GSD);

			//m_testEmitter->Tick(m_GSD);

			//adjust the camera pan or zoom
			//find average and furthest points of players locations
			Vector2 top_left = Vector2(100000, 100000);
			Vector2 bottom_right = Vector2(-1000, -1000);
			Vector2 avg_pos = Vector2::Zero;
			int num_players = 0;

			for (int i = 0; i < 4; i++)
			{
				if (players[i])
				{
					if (players[i]->GetLives() > 0)
					{
						Vector2 p = players[i]->GetPos();
						avg_pos += (p * m_cam_zoom);

						top_left.x = (p.x < top_left.x) ? p.x : top_left.x;
						top_left.y = (p.y < top_left.y) ? p.y : top_left.y;

						bottom_right.x = (p.x > bottom_right.x) ? p.x : bottom_right.x;
						bottom_right.y = (p.y > bottom_right.y) ? p.y : bottom_right.y;

						num_players++;
					}
				}
			}

			//if there are fewer then 2 players or no time left
			if (num_players <= 1 || m_timeLeft <= 0)
			{
				m_game_over_check = GameOverCheck::WAIT;
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

				if (m_game_over_check != GameOverCheck::FREEZE)
				{
					m_cam_zoom = m_zoom_rate / pow(dist, 1.05f);
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
			}

			if (!m_infiniteTime)
			{
				m_timeLeft -= timer.GetElapsedSeconds();
			}
		}

		//spawning items

		m_spawn_item_time += m_GSD->m_dt;
		if (m_spawn_item_time > 10)
		{
			std::string st = item_spawner.getRandomItemName();

			if (st != "No items available")
			{
				giveMeItem(m_RD, m_GSD, st, game_stage->getRandomSpawnPoint());
			}
			m_spawn_item_time = 0;	
		}

	}

	if(m_game_over_check != GameOverCheck::NONE)
	{
		m_game_over_timer[(int)m_game_over_check] += timer.GetElapsedSeconds();

		if (m_game_over_timer[0] >= 0.5f)
		{
			m_game_over_check = GameOverCheck::FREEZE;
		}
		if (m_game_over_timer[1] >= 1.5f)
		{
			for (int i = 0; i < listeners.size(); i++)
			{
				listeners[i]->onNotify(nullptr, Event::GAME_OVER);
			}
		}
	}
}

void GameScene::Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList)
{
	Scene::Render(_commandList);

	ID3D12DescriptorHeap* heaps[] = { m_RD->m_resourceDescriptors->Heap() };
	_commandList->SetDescriptorHeaps(_countof(heaps), heaps);
	m_RD->m_spriteBatch->Begin(_commandList.Get());
	if (m_HUD)
	{
		m_HUD->Render(m_RD);
	}

	std::wstring text = L"PAUSED";

	if (paused)
	{
		//render a pause text
		m_pause_text->Render(m_RD, 0);
	}

	m_RD->m_spriteBatch->End();
}

void GameScene::giveMeItem(RenderData * _RD, GameStateData* _GSD, std::string _name, Vector2 _pos)
{
	Item* itm = item_spawner.createNewItemWithName(_RD,_name);
	itm->SetSpawn(_pos);

	m_spawner->onNotify(itm, Event::OBJECT_INSTANTIATED);
	//_GSD->objects_in_scene.push_back(itm->GetPhysics());
	//m_2DObjects.push_back(itm);
}

void GameScene::Reset()
{
	m_cam_pos = Vector2::Zero;
	m_cam_zoom = 1;

	//attaching values of game settings handler to scene
	for (int i = 0; i < listeners.size(); i++)
	{
		if (listeners[i]->getType() == "GameSettings")
		{
			GameSettingsHandler* temp = static_cast<GameSettingsHandler*>(listeners[i]);
			m_infiniteLives = temp->getInfiniteLives();
			m_infiniteTime = temp->getInfiniteTime();
			m_maxLives = temp->getLives();
			m_timeLimit = temp->getTime();
			m_timeLeft = m_timeLimit;

			if (temp->isStageSelected())
			{
				game_stage = stage_manager.returnSceneWithIndex(temp->getStageSelected());
				//adds all 2d objects to the stage
				game_stage->addObjectsToScene(m_2DObjects,m_GSD);

				//give the player a spawn point
				for (int j = 0; j < 4; j++)
				{
					if (players[j] != nullptr)
					{
						players[j]->SetSpawn(game_stage->getSpawn(j));
					}
				}
			


				temp->setIsStageSelected(false);
			}
		
		

			item_spawner.assignAvailability(temp->GetAvailableItems());
			
		}
	}



	for (int i = 0; i < 4; i++)
	{
		if (players[i])
		{
			players[i]->ResetDamage();
		}
	}

	for (int i = 0; i < m_GSD->objects_in_scene.size(); i++)
	{
		m_GSD->objects_in_scene[i]->ResetForce(BOTH_AXES);
	}
	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		m_2DObjects[i]->ResetPos();
	}

	for (int i = 0; i < m_3DObjects.size(); i++)
	{
		m_3DObjects[i]->ResetPos();
	}

	m_game_over_check = GameOverCheck::NONE;
	m_game_over_timer[0] = 0;
	m_game_over_timer[1] = 0;
}

void GameScene::LinkSettings()
{
	//attaching values of game settings handler to scene
	for (int i = 0; i < listeners.size(); i++)
	{
		if (listeners[i]->getType() == "GameSettings")
		{
			GameSettingsHandler* temp = static_cast<GameSettingsHandler*>(listeners[i]);
			m_infiniteLives = temp->getInfiniteLives();
			m_infiniteTime = temp->getInfiniteTime();
			m_maxLives = temp->getLives();
			m_timeLimit = temp->getTime();
			m_timeLeft = m_timeLimit;

			item_spawner.assignAvailability(temp->GetAvailableItems());
		}
	}
}
