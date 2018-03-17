#include "pch.h"
#include "HUD.h"
#include "GameStateData.h"

HUD::HUD(GameStateData* _GSD)
{
	for (int i = 0; i < 4; i++)
	{
		m_in_game[i].in_game = false;

		int x = (_GSD->window_size.x - 350) * (i % 2);
		int y = (_GSD->window_size.y - 100) * (i / 2);

		Vector2 pos = Vector2(x, y);

		m_text_display[i] = new Text2D("Test");
		m_text_display[i]->SetPos(pos);

		//shadow and highlight help the text to stand out
		m_highlight[i] = new Text2D("Test");
		m_highlight[i]->SetPos(pos - Vector2(0.5f, 0.5f));
		m_highlight[i]->SetColour(Color(1, 1, 1));
		m_shadow[i] = new Text2D("Test");
		m_shadow[i]->SetPos(pos + Vector2(0.5f, 0.5f));
		m_shadow[i]->SetColour(Color(0, 0, 0));
	}

	m_text_display[0]->SetColour(Color(0.3, 0.3, 1));
	m_text_display[1]->SetColour(Color(0, 0.7, 0));
	m_text_display[2]->SetColour(Color(1, 0, 0));
	m_text_display[3]->SetColour(Color(1, 1, 0));
}

HUD::~HUD()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_text_display[i])
		{
			delete m_text_display[i];
			m_text_display[i] = nullptr;
		}
		if (m_highlight[i])
		{
			delete m_highlight[i];
			m_highlight[i] = nullptr;
		}
		if (m_shadow[i])
		{
			delete m_shadow[i];
			m_shadow[i] = nullptr;
		}
	}
}

void HUD::AddCharacter(Character * _char)
{
	for (int i = 0; i < 4; i++)
	{
		if (!m_in_game[i].in_game)
		{
			m_in_game[i].character = _char;
			m_in_game[i].in_game = true;
			break;
		}
	}
}

void HUD::RemoveCharacter(Character * _char)
{
	for (int i = 0; i < 4; i++)
	{
		if (m_in_game[i].character == _char)
		{
			m_in_game[i].in_game = false;
		}
	}
}

void HUD::Render(RenderData * _RD)
{
	for (int i = 0; i < 4; i++)
	{
		if (m_in_game[i].in_game)
		{
			std::string display_text = m_in_game[i].character->GetName();
			display_text += "\n";
			display_text += std::to_string(m_in_game[i].character->GetDamage()) + "%";
			display_text += " ";
			display_text += std::to_string(m_in_game[i].character->GetLives());

			m_shadow[i]->SetText(display_text);
			m_shadow[i]->Render(_RD);
			m_highlight[i]->SetText(display_text);
			m_highlight[i]->Render(_RD);
			m_text_display[i]->SetText(display_text);
			m_text_display[i]->Render(_RD);
		}
	}
}