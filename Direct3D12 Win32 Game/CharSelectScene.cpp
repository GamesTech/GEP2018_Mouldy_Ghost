#include "pch.h"
#include "CharSelectScene.h"
#include "RenderData.h"
#include "GameScene.h"


CharacterSelectScene::CharacterSelectScene(GameScene* _g_scene)
{
	m_gameScene = _g_scene;
	m_ch_manager = m_gameScene->GetCharacterManager();

	m_player_tints[0] = SimpleMath::Color(0.3, 1, 1);
	m_player_tints[1] = SimpleMath::Color(0.3, 1, 0.3);
	m_player_tints[2] = SimpleMath::Color(1, 0.3, 0.3);
	m_player_tints[3] = SimpleMath::Color(1, 1, 0.3);

	m_instructions[0] = new Text2D("Left/Right -\n\nA -\n\nStart/Menu -\n\nBack/View -");
	m_instructions[0]->SetPos(Vector2(0, 0));
	m_instructions[1]= new Text2D("Select Character\n\nConfirm Character\n\nStart Game\n\nReturn to Menu");
	m_instructions[1]->SetPos(Vector2(400, 0));
}

CharacterSelectScene::~CharacterSelectScene()
{
	delete m_instructions[0];
	delete m_instructions[1];
}

void CharacterSelectScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	for (int i = 0; i < 4; i++)
	{
		if (m_GSD->menu_action[i] == MenuAction::NAV_LEFT && !m_confirmed[i])
		{
			m_selected_character[i]--;
		}
		if (m_GSD->menu_action[i] == MenuAction::NAV_RIGHT && !m_confirmed[i])
		{
			m_selected_character[i] = (m_selected_character[i] + 1)
				% (m_ch_manager->GetCharCount() + 1);
		}

		if (m_selected_character[i] < 0)
		{
			m_selected_character[i] = m_ch_manager->GetCharCount();
		}
		if ((m_GSD->menu_action[i] == MenuAction::CONFIRM) && isValid(i))
		{
			m_confirmed[i] = !m_confirmed[i];
		}

		if ((m_GSD->menu_action[i] == MenuAction::ADVANCE_MENU))
		{
			bool all_confirmed = true;
			for (int j = 0; j < 4; j++)
			{
				if (isValid(j) && !m_confirmed[j])
				{
					all_confirmed = false;
				}
			}

			if (all_confirmed)
			{
				for (int j = 0; j < 4; j++)
				{
					if (isValid(j))
					{
						std::string character_name =
							m_ch_manager->GetCharacter(m_selected_character[j]).GetName();

						m_gameScene->AddCharacter(j, character_name, m_RD);
					}
				}
				for (int j = 0; j < listeners.size(); j++)
				{
					Reset();
					listeners[j]->onNotify(nullptr, Event::CHANGE_SCENE_GAME);
				}
			}
		}

		if((m_GSD->menu_action[i] == MenuAction::PREVIOUS_MENU))
		{
			if (isValid(i))
			{
				m_selected_character[i] = m_ch_manager->GetCharCount();
				m_confirmed[i] = false;
			}
			else
			{
				for (int j = 0; j < listeners.size(); j++)
				{
					Reset();
					listeners[j]->onNotify(nullptr, Event::CHANGE_SCENE_MELEE_MENU);
				}
			}
		}
	}
}

void CharacterSelectScene::Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList, Vector2 _camera_position)
{
	//primative batch
	m_RD->m_effect->SetProjection(m_cam->GetProj());
	m_RD->m_effect->SetView(m_cam->GetView());
	m_RD->m_effect->Apply(_commandList.Get());
	m_RD->m_effect->EnableDefaultLighting();
	ID3D12DescriptorHeap* heaps[] = { m_RD->m_resourceDescriptors->Heap() };
	_commandList->SetDescriptorHeaps(_countof(heaps), heaps);
	m_RD->m_spriteBatch->Begin(_commandList.Get());

	m_instructions[0]->Render(m_RD);
	m_instructions[1]->Render(m_RD);

	for (int i = 0; i < 4; i++)
	{
		if (m_selected_character[i] != m_ch_manager->GetCharCount())
		{
			Character c = m_ch_manager->GetCharacter(m_selected_character[i]);

			if (m_confirmed[i])
			{
				c.SetColour(m_player_tints[i]);
			}

			int x = m_GSD->window_size.x / 3 * ((i % 2) + 1);
			int y = m_GSD->window_size.y / 3 * ((i / 2) + 1);

			c.SetPos(Vector2(x, y));
			c.Render(m_RD);
		}
	}

	m_RD->m_spriteBatch->End();
}

void CharacterSelectScene::Reset()
{
	for (int i = 0; i < 4; i++)
	{
		m_confirmed[i] = false;
		m_selected_character[i] = m_ch_manager->GetCharCount();
	}
}

void CharacterSelectScene::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	m_cam = new Camera(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam;
	m_3DObjects.push_back(m_cam);

	for (int i = 0; i < 4; i++)
	{
		m_selected_character[i] = m_ch_manager->GetCharCount();
	}
}

bool CharacterSelectScene::isValid(int i)
{
	return m_selected_character[i] < m_ch_manager->GetCharCount()
		&& m_selected_character >= 0;
}