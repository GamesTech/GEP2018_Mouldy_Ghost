#include "pch.h"
#include "Text2D.h"
#include "renderdata.h"
#include "ControllerFont.h"
#include <codecvt>


Text2D::Text2D(string _text)
{
	SetText(_text);
}

void Text2D::SetText(string _text)
{
	m_text = _text;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	m_wText = converter.from_bytes(m_text.c_str());
}

Text2D::~Text2D()
{
}

void Text2D::CentreOrigin()
{
	m_dirtyOrigin = true;
}

void Text2D::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom)
{
	if (m_dirtyOrigin)
	{
		//needs to be done here as reuqires the font being used
		//so made  this hack
		m_dirtyOrigin = false;
		m_origin = _RD->m_font->MeasureString(m_wText.c_str()) / 2.f;
	}
	DX::DrawControllerString(_RD->m_spriteBatch.get(), _RD->m_font.get(), _RD->m_controller_font.get(), m_wText.c_str(), m_pos, m_colour, m_scale);
	//_RD->m_font->DrawString(_RD->m_spriteBatch.get(), m_wText.c_str(), m_pos, m_colour, m_orientation, m_scale);
}

int Text2D::GetWidth(RenderData * _RD)
{
	return _RD->m_font->MeasureString(m_wText.c_str()).m128_f32[0];
}
