#include "pch.h"
#include "InputTextBox.h"
#include "GameStateData.h"

InputTextBox::InputTextBox(RenderData* _RD, Vector2 _pos)
	: Button(_RD, "TextBox", "Pop", _pos, Vector2(1,1))
{
	m_selected = false;
	m_contents = std::make_unique<Text2D>("");
	m_contents->SetPos(m_pos);

	m_bounds.x = _pos.x;
	m_bounds.y = _pos.y;
	m_bounds.width = GetTextureSize(allTextures[m_textureIndex].texture.Get()).x;
	m_bounds.height = GetTextureSize(allTextures[m_textureIndex].texture.Get()).y;

	Color c = Colors::Black;
	m_contents->SetColour(c);
}

void InputTextBox::CentreOrigin()
{
}

void InputTextBox::Tick(GameStateData * _GSD)
{
	mouseUpdate(_GSD);
	if (m_selected)
	{
		bool need_update = false;
		//letters
		for (int i = 0x41; i < 0x5b && m_text_in_box.size() < 16; i++)
		{
			if (keyPress((Keyboard::Keys)i, _GSD))
			{
				if (_GSD->m_keyboardState.IsKeyDown(Keyboard::Keys::LeftShift)
					|| _GSD->m_keyboardState.IsKeyDown(Keyboard::Keys::RightShift))
				{
					m_text_in_box.push_back((char)i);
					need_update = true;
					break;
				}
				else
				{
					m_text_in_box.push_back((char)i + 32);
					need_update = true;
					break;
				}
			}
		}

		//numbers
		for (int i = 0x60; i < 0x70 && m_text_in_box.size() < 16; i++)
		{
			if (keyPress((Keyboard::Keys)i, _GSD))
			{
				m_text_in_box.push_back((char)(i - 48));
				need_update = true;
				break;
			}
		}
		for (int i = 0x30; i < 0x40 && m_text_in_box.size() < 16; i++)
		{
			if (keyPress((Keyboard::Keys)i, _GSD))
			{
				m_text_in_box.push_back((char)i);
				need_update = true;
				break;
			}
		}
		//space
		if (keyPress(Keyboard::Keys::Space, _GSD))
		{
			m_text_in_box.push_back(0x20);
			need_update = true;
		}
		//backspace
		if (keyPress(Keyboard::Keys::Back, _GSD))
		{
			m_text_in_box.pop_back();
			need_update = true;
		}

		if (need_update)
		{
			updateContents();
		}
	}
}

void InputTextBox::Render(RenderData * _RD)
{
	ImageGO2D::Render(_RD);
	m_contents->Render(_RD);
}

void InputTextBox::mouseUpdate(GameStateData * _GSD)
{
	if (_GSD->m_mouseState.leftButton)
	{
		m_selected = m_bounds.Contains(_GSD->m_cursor->GetPos());
	}
}

void InputTextBox::updateContents()
{
	std::string contents = "";
	for (char c : m_text_in_box)
	{
		contents += c;
	}
	m_contents->SetText(contents);
}

bool InputTextBox::keyPress(Keyboard::Keys _key, GameStateData* _GSD)
{
	return _GSD->m_keyboardState.IsKeyDown(_key)
		&& !_GSD->m_prevKeyboardState.IsKeyDown(_key);
}
