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

	m_instructions[0] = new Text2D("[LThumb]\n\n[A]\n\n[Start]\n\n[Back]");
	m_instructions[0]->SetPos(Vector2(50, 50));
	m_instructions[1]= new Text2D("- Select Character\n\n- Confirm Character\n\n- Start Game\n\n- Return to Menu");
	m_instructions[1]->SetPos(Vector2(350, 50));
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
		//adding and removing ai
		if (m_GSD->menu_action[i] == MenuAction::NAV_UP)
		{
			addAI();
		}
		if (m_GSD->menu_action[i] == MenuAction::NAV_DOWN)
		{
			removeAI();
		}

		//left and right to select characters
		if (m_GSD->menu_action[i] == MenuAction::NAV_LEFT && !m_confirmed[i])
		{
			m_selected_character[i]--;
		}
		if (m_GSD->menu_action[i] == MenuAction::NAV_RIGHT && !m_confirmed[i])
		{
			m_selected_character[i] = (m_selected_character[i] + 1)
				% (m_ch_manager->GetCharCount() + 1);
		}

		if ((m_GSD->menu_action[i] == MenuAction::NAV_LEFT
			|| m_GSD->menu_action[i] == MenuAction::NAV_RIGHT)
			&& ai_to_add[i] != "")
		{
			removeAI(i);
		}

		//if they go below 0, loop back to the last one
		if (m_selected_character[i] < 0)
		{
			m_selected_character[i] = m_ch_manager->GetCharCount();
		}
		//check for a valid selection and confirm their player
		if ((m_GSD->menu_action[i] == MenuAction::CONFIRM) && isValid(i))
		{
			m_confirmed[i] = !m_confirmed[i];
		}

		//if someone pressed the advance menu button
		if ((m_GSD->menu_action[i] == MenuAction::ADVANCE_MENU))
		{
			bool all_confirmed = true;
			int numPlayers = 0;
			for (int j = 0; j < 4; j++)
			{
				//if a player has a character highlighted and
				//not selected, don't let the menu advance
				if (isValid(j) && !m_confirmed[j])
				{
					all_confirmed = false;
				}
				if (m_confirmed[j])
				{
					numPlayers++;
				}
			}

			//if there is one or fewer confirmed players
			//don't advance
			if (numPlayers <= 1)
			{
				all_confirmed = false;
			}

			//if the menu can advance
			if (all_confirmed)
			{
				for (int j = 0; j < 4; j++)
				{
					if (ai_to_add[j] != "")
					{
						m_gameScene->AddCharacter(j, ai_to_add[j], true);
					}
					else if (isValid(j))
					{
						//add the character to the game scene
						std::string character_name =
							m_ch_manager->GetCharacter(m_selected_character[j]).GetName();

						m_gameScene->AddCharacter(j, character_name, false);
					}
				}
				Reset();
				for (int j = 0; j < listeners.size(); j++)
				{
					listeners[j]->onNotify(nullptr, Event::CHANGE_SCENE_STAGE_SELECT);
				}
			}
		}

		if((m_GSD->menu_action[i] == MenuAction::PREVIOUS_MENU))
		{
			//if the player has a highlighted character, deselect it
			if (isValid(i))
			{
				m_selected_character[i] = m_ch_manager->GetCharCount();
				m_confirmed[i] = false;
			}
			//otherwise quit to the previous menu
			else
			{
				for (int j = 0; j < listeners.size(); j++)
				{
					listeners[j]->onNotify(nullptr, Event::CHANGE_SCENE_MELEE_MENU);
				}
			}
		}
	}
}

void CharacterSelectScene::Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList)
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
	//on leaving this scene, link the game settings to the game scene
	for (int i = 0; i < 4; i++)
	{
		m_confirmed[i] = false;
		m_selected_character[i] = m_ch_manager->GetCharCount();
	}
	m_gameScene->LinkSettings();
}

void CharacterSelectScene::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	m_cam = std::make_unique<Camera>(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam.get();
	m_3DObjects.push_back(m_cam.get());

	for (int i = 0; i < 4; i++)
	{
		m_selected_character[i] = m_ch_manager->GetCharCount();
	}
}

void CharacterSelectScene::addAI()
{
	for (int i = 0; i < 4; i++)
	{
		if (!isValid(i) && ai_to_add[i] == "")
		{
			int r = rand() % m_ch_manager->GetCharCount();
			Character c = m_ch_manager->GetCharacter(r);
			ai_to_add[i] = c.GetName();
			m_selected_character[i] = r;
			m_confirmed[i] = true;
			break;
		}
	}
}

void CharacterSelectScene::removeAI()
{
	for (int i = 3; i > -1; i--)
	{
		if (ai_to_add[i] != "")
		{
			ai_to_add[i] = "";
			m_confirmed[i] = false;
			m_selected_character[i] = m_ch_manager->GetCharCount();
			break;
		}
	}
}

void CharacterSelectScene::removeAI(int i)
{
	ai_to_add[i] = "";
	m_confirmed[i] = false;
}

bool CharacterSelectScene::isValid(int i)
{
	//character is selected
	return m_selected_character[i] < m_ch_manager->GetCharCount()
		&& m_selected_character >= 0;
}