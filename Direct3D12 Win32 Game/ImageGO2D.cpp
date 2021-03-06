#include "pch.h"
#include "ImageGO2D.h"
#include <codecvt>
#include "RenderData.h"

ImageGO2D::ImageGO2D(RenderData * _RD, string _filename)
{
	bool texture_found = false;
	for (int i = 0; i < allTextures.size(); i++)
	{
		if (allTextures[i].textureName == _filename)
		{
			//do something here
			texture_found = true;
			m_textureIndex = i;
			m_resourceNum = allTextures[i].resource_num;
		}
	}

	if (!texture_found)
	{
		TextureItem temp;
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		string fullpath = "../DDS/" + _filename + ".dds";
		std::wstring wFilename = converter.from_bytes(fullpath.c_str());

		ResourceUploadBatch resourceUpload(_RD->m_d3dDevice.Get());

		resourceUpload.Begin();

		DX::ThrowIfFailed(
			CreateDDSTextureFromFile(_RD->m_d3dDevice.Get(), resourceUpload, wFilename.c_str(),
				temp.texture.ReleaseAndGetAddressOf()));


		CreateShaderResourceView(_RD->m_d3dDevice.Get(), temp.texture.Get(),
			_RD->m_resourceDescriptors->GetCpuHandle(m_resourceNum = _RD->m_resourceCount++));

		auto uploadResourcesFinished = resourceUpload.End(_RD->m_commandQueue.Get());

		uploadResourcesFinished.wait();

		m_textureIndex = allTextures.size();

		temp.textureName = _filename;
		temp.resource_num = m_resourceNum;
		allTextures.push_back(temp);
	}

	m_spriteSize = Vector2(GetTextureSize(allTextures[m_textureIndex].texture.Get()).x,
		GetTextureSize(allTextures[m_textureIndex].texture.Get()).y);
	CentreOrigin();
}

ImageGO2D::~ImageGO2D()
{
	//m_texture.Reset();
}

void ImageGO2D::SetSpriteSize(Vector2 _size, int _sprites_in_row)
{
	m_spriteSize = _size;
	m_sprites_in_row = _sprites_in_row;
}

void ImageGO2D::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom)
{
	Rectangle rect = Rectangle(0, 0, m_spriteSize.x, m_spriteSize.y);
	const RECT* r = &RECT(rect);

	Vector2 render_scale = m_scale * _zoom;

	Vector2 distance_from_origin = m_pos - _cam_pos;
	distance_from_origin *= _zoom;

	Vector2 render_pos = ((2 * _zoom) * _cam_pos) + distance_from_origin;

	if (!flipped)
	{
		_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
			GetTextureSize(allTextures[m_textureIndex].texture.Get()),
			render_pos, r, m_colour, m_orientation, m_origin, render_scale);
	}
	else
	{
		_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
			GetTextureSize(allTextures[m_textureIndex].texture.Get()),
			render_pos, r, m_colour, m_orientation, m_origin, render_scale, SpriteEffects::SpriteEffects_FlipHorizontally, 0);
	}
}

void ImageGO2D::CentreOrigin()
{
	XMUINT2 size = GetTextureSize(allTextures[m_textureIndex].texture.Get());
	
	m_origin = Vector2(float(size.x / 2), float(size.y / 2));
}

Vector2 ImageGO2D::TextureSize()
{
	if (m_spriteSize.x == 0)
	{
		XMUINT2 size = GetTextureSize(allTextures[m_textureIndex].texture.Get());
		return Vector2(size.x, size.y);
	}
	else
	{
		return m_spriteSize;
	}
}

std::vector<TextureItem> ImageGO2D::allTextures;