#include "pch.h"
#include "Button.h"

Button::Button(RenderData * _RD, string _filename, std::string _text, Vector2 _position, Vector2 _scale)
	: ImageGO2D(_RD, _filename)
{
	SetPos(_position);
	SetScale(_scale);
	m_bounds.x = _position.x;
	m_bounds.y = _position.y;
	m_bounds.width = _scale.x * GetTextureSize(allTextures[m_textureIndex].texture.Get()).x;
	m_bounds.height = _scale.y * GetTextureSize(allTextures[m_textureIndex].texture.Get()).y;

	text.CentreOrigin();
	setText(_text);
	Vector2 text_position;
	text_position.x = m_bounds.x + 45;
	text_position.y = m_bounds.y + 25;

	text.SetPos(text_position);
}

void Button::setText(std::string _text)
{
	text.SetText(_text);
}

void Button::Render(RenderData * _RD)
{
	ImageGO2D::Render(_RD);
	text.Render(_RD);
}