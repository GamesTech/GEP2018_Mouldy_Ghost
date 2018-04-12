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

	m_text_colours[0] = (Color(0.3, 0.3, 1));
	m_text_colours[1] = (Color(0, 0.7, 0));
	m_text_colours[2] = (Color(1, 0, 0));
	m_text_colours[3] = (Color(1, 1, 0));

	m_timeText = new Text2D("");
	m_timeText->SetPos(Vector2((_GSD->window_size.x / 2) - 100,25));


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
	//iterate through each character
	for (int i = 0; i < 4; i++)
	{
		//find the first empty space
		if (!m_in_game[i].in_game)
		{
			//add the character
			m_in_game[i].character = _char;
			m_in_game[i].in_game = true;
			//don't continue trying to add this character
			break;
		}
	}
}

void HUD::RemoveCharacter(Character * _char)
{
	//find the character in the hud
	for (int i = 0; i < 4; i++)
	{
		if (m_in_game[i].character == _char)
		{
			//remove them
			m_in_game[i].character = nullptr;
			m_in_game[i].in_game = false;
		}
	}
}

void HUD::attachTimerPointer(float * _timer)
{
	m_timer = _timer;
}

void HUD::Render(RenderData * _RD)
{
	for (int i = 0; i < 4; i++)
	{
		//character in game and alive
		if (m_in_game[i].in_game && m_in_game[i].character->GetLives() > 0)
		{
			//set colour to the one associated with their player number
			m_text_display[i]->SetColour
			(m_text_colours[m_in_game[i].character->GetControllerIndex()]);
			//show their name
			std::string display_text = m_in_game[i].character->GetName();
			display_text += "\n";
			//show their damage
			display_text += std::to_string(m_in_game[i].character->GetDamage()) + "%";
			display_text += " ";
			//show their lives
			display_text += std::to_string(m_in_game[i].character->GetLives());
			
			//show the shadow and highlight on the text
			//check if we're on infinite lives
			if (m_in_game[i].character->GetLives() < 20)
			{
				display_text += std::to_string(m_in_game[i].character->GetLives());
			}

			m_shadow[i]->SetText(display_text);
			m_shadow[i]->Render(_RD);
			m_highlight[i]->SetText(display_text);
			m_highlight[i]->Render(_RD);
			m_text_display[i]->SetText(display_text);
			m_text_display[i]->Render(_RD);
		}
	}

	//check we're not running on infinite time
	if (*m_timer < 3060)
	{
		int tempTime = static_cast<int>(*m_timer);
		int minutes = tempTime / 60;

		int seconds = tempTime - (minutes * 60);
		std::string seconds_string = "";
		if (seconds < 10)
		{
			seconds_string += "0";
		}
		seconds_string += std::to_string(seconds);

		int hundrethSecond = (*m_timer - tempTime) * 100;
		std::string hundrethString = "";
		if (hundrethSecond < 10)
		{
			hundrethString += "0";
		}
		hundrethString += std::to_string(hundrethSecond);
		std::string timeOutput = std::to_string(minutes) + ":" + seconds_string + ":" + hundrethString;

		m_timeText->SetText(timeOutput);
		m_timeText->Render(_RD);
	}
}