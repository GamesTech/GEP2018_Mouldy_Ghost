#include "pch.h"
#include "ClickableButton.h"
#include "GameStateData.h"

ClickableButton::ClickableButton
(RenderData * _RD, string _filename, std::string _text, Event _return_scene, Vector2 _position, Vector2 _scale)
	: ImageGO2D(_RD, _filename)
{
	SetPos(_position);
	SetScale(_scale);
	bounds.x = _position.x - ((GetTextureSize(allTextures[m_textureIndex].texture.Get()).x / 2) * _scale.x);
	bounds.y = _position.y - ((GetTextureSize(allTextures[m_textureIndex].texture.Get()).y / 2) * _scale.y);
	bounds.width = _scale.x * GetTextureSize(allTextures[m_textureIndex].texture.Get()).x;
	bounds.height = _scale.y * GetTextureSize(allTextures[m_textureIndex].texture.Get()).y;

	setText(_text);
	Vector2 text_position;
	text.SetScale(_scale * 10);
	text_position.x = bounds.x + ((GetTextureSize(allTextures[m_textureIndex].texture.Get()).x / 10) * _scale.x);
	text_position.y = bounds.y + ((GetTextureSize(allTextures[m_textureIndex].texture.Get()).y / 4) * _scale.y);
	
	text.SetPos(text_position);
	//text.CentreOrigin();
	return_scene = _return_scene;
}

void ClickableButton::Render(RenderData* _RD, int _sprite,
	Vector2 _cam_pos, float _zoom)
{
	ImageGO2D::Render(_RD);
	text.Render(_RD);
}

void ClickableButton::setText(std::string _text)
{
	text.SetText(_text);
}

Event* ClickableButton::mouseUpdate(Cursor* _cursor, GameStateData * _GSD)
{
	if (bounds.Contains(_cursor->GetPos()))
	{
		m_colour.B(0.4f);
		if (_GSD->m_mouseState.leftButton)
		{
			pressedLastFrame = true;
		}

		if (!_GSD->m_mouseState.leftButton && pressedLastFrame)
		{
			pressedLastFrame = false;
			return &return_scene;
		}
	}
	else
	{
		m_colour.B(1.0f);
	}

	return nullptr;
}

Event ClickableButton::getEvent()
{
	return return_scene;
}
