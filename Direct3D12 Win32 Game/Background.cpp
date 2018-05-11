#include "pch.h"
#include "Background.h"
#include "RenderData.h"

Background::Background(RenderData * _RD, string _filename, int _layer) : ImageGO2D(_RD, _filename)
{
	m_physics = std::make_shared<Physics2D>();
	CentreOrigin();
	m_layer = _layer;
}

Background::~Background()
{
}

void Background::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom)
{
	_cam_pos *= pow(1.1, m_layer);

	Rectangle rect = Rectangle(0, 0, m_spriteSize.x, m_spriteSize.y);
	const RECT* r = &RECT(rect);

	Vector2 render_scale = m_scale * _zoom;

	Vector2 distance_from_origin = m_pos - _cam_pos;
	distance_from_origin *= _zoom;

	Vector2 render_pos = ((2 * _zoom) * _cam_pos) + distance_from_origin;

	_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
		GetTextureSize(allTextures[m_textureIndex].texture.Get()),
		render_pos, r, m_colour, m_orientation, m_origin, m_scale);
}