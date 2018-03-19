#include "pch.h"
#include "GameScene.h"
#include "RenderData.h"
#include "GameStateData.h"
#include "FinalDestination.h"
#include "CharacterController.h"
#include "Player.h"
#include "SpawnHandler.h"

GameScene::GameScene()
{
	player_tints[0] = SimpleMath::Color(0.3, 1, 1);
	player_tints[1] = SimpleMath::Color(0.3, 1, 0.3);
	player_tints[2] = SimpleMath::Color(1, 0.3, 0.3);
	player_tints[3] = SimpleMath::Color(1, 1, 0.3);

	m_2DObjects.reserve(256);
}

GameScene::~GameScene()
{
	for (int i = 0; i < 4; i++)
	{
		if (entities[i])
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}

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

	m_spawner = std::make_unique<SpawnHandler>();
	m_spawner->setData(&m_2DObjects, &m_GSD->objects_in_scene, m_RD);

	item_spawner = ItemSpawner(m_spawner.get());

	c_manager.PopulateCharacterList(_RD, m_spawner.get());
	item_spawner.loadAllData(_RD);

	//GEP::This is where I am creating the test objects
	m_cam = new Camera(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam;
	m_3DObjects.push_back(m_cam);

	//creating a stage
	//could pass the name of the stage as a function paratemter
	game_stage = std::make_unique<FinalDestination>();
	game_stage->init(m_RD,m_GSD);

	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		for (int j = 0; j < listeners.size(); j++)
		{
			m_2DObjects[i]->addListener(listeners[j]);
		}
	}

	giveMeItem(_GSD, "apple");

	game_stage->addObjectsToScene(m_2DObjects);

	for (int i = 0; i < 4; i++)
	{
		entities[i] = new Player(i);
	}
}

void GameScene::AddCharacter(int i, std::string _character, RenderData * _RD)
{
	if (players[i])
	{
		RemoveCharacter(players[i]);
	}
	players[i] = new Character(c_manager.GetCharacter(_character));
	players[i]->SetSpawn(Vector2(i * 100 + 500, 100));
	players[i]->SetColour(player_tints[i]);

	players[i]->CreatePhysics(_RD);
	players[i]->GetPhysics()->SetDrag(0.5f);
	players[i]->GetPhysics()->SetBounce(0.4f);

	float width = players[i]->TextureSize().x / 2;
	float height = players[i]->TextureSize().y;
	Rectangle rect = Rectangle
	(players[i]->GetPos().x, players[i]->GetPos().y, width, height);
	players[i]->GetPhysics()->SetCollider(rect);

	m_2DObjects.push_back(players[i]);
	m_GSD->objects_in_scene.push_back(players[i]->GetPhysics());
	entities[i]->SetCharacter(players[i]);

	m_HUD->AddCharacter(players[i]);
}

void GameScene::RemoveCharacter(Character* _char)
{
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

	delete _char;
	_char = nullptr;
}

void GameScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	Scene::Update(timer, _audEngine);
	game_stage->update(m_GSD);

	//find average of players location
	int average_x = 0;
	int average_y = 0;
	int num_players = 0;

	for (int i = 0; i < 4; i++)
	{
		if (players[i])
		{
			if (players[i]->GetLives() > 0)
			{
				average_x += players[i]->GetPos().x;
				average_y += players[i]->GetPos().y;
				num_players++;
			}
		}
	}
	if (num_players == 1)
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, Event::GAME_OVER);
		}
	}
	else if (num_players)
	{
		average_x /= num_players;
		average_y /= num_players;

		Vector2 average_pos = Vector2(average_x, average_y);
		Vector2 mid = (m_GSD->window_size / 2);
		Vector2 cam_target = (average_pos * -1) + mid;
		Vector2 dir_to_target = cam_target - m_cam_pos;
		m_cam_pos += dir_to_target / 20;
	}

	//if (m_GSD->game_actions[0].size() > 0)
	//{
	//	//code for testing zoom
	//	if (m_GSD->game_actions[0][0] == GameAction::P_RELEASE_SPECIAL)
	//	{
	//		for (int i = 0; i < m_2DObjects.size(); i++)
	//		{
	//			ImageGO2D* temp = static_cast<ImageGO2D*>(m_2DObjects[i]);
	//			temp->scaleFromPoint(m_cam_pos, Vector2(temp->GetScale().x + 0.1f, temp->GetScale().y + 0.1f));
	//		}
	//	}
	//	if (m_GSD->game_actions[0][0] == GameAction::P_RELEASE_BASIC)
	//	{
	//		for (int i = 0; i < m_2DObjects.size(); i++)
	//		{
	//			ImageGO2D* temp = static_cast<ImageGO2D*>(m_2DObjects[i]);
	//			temp->scaleFromPoint(m_cam_pos, Vector2(temp->GetScale().x - 0.1f, temp->GetScale().y - 0.1f));
	//		}
	//	}
	//}
}

void GameScene::Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList,
	Vector2 _camera_position)
{
	Scene::Render(_commandList, m_cam_pos);

	ID3D12DescriptorHeap* heaps[] = { m_RD->m_resourceDescriptors->Heap() };
	_commandList->SetDescriptorHeaps(_countof(heaps), heaps);
	m_RD->m_spriteBatch->Begin(_commandList.Get());
	m_HUD->Render(m_RD);
	m_RD->m_spriteBatch->End();
}

void GameScene::giveMeItem(GameStateData* _GSD, std::string _name)
{
	Item* itm = item_spawner.createNewItemWithName(_name);
	itm->SetSpawn(Vector2(500,100));

	m_spawner->onNotify(itm, Event::OBJECT_INSTANTIATED);
	//_GSD->objects_in_scene.push_back(itm->GetPhysics());
	//m_2DObjects.push_back(itm);
}

void GameScene::Reset()
{
	m_cam_pos = Vector2::Zero;

	for (int i = 0; i < 4; i++)
	{
		if (players[i])
		{
			players[i]->ResetDamage();
			players[i]->ResetLives();
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
}