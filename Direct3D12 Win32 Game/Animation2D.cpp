#include "pch.h"
#include "Animation2D.h"
#include "RenderData.h"
#include "GameStateData.h"




Animation2D::Animation2D(RenderData * _RD, string _filename, int _resourceNum)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	string fullpath = "../DDS/" + _filename + ".dds";
	std::wstring wFilename = converter.from_bytes(fullpath.c_str());

	ResourceUploadBatch resourceUpload(_RD->m_d3dDevice.Get());

	resourceUpload.Begin();

	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(_RD->m_d3dDevice.Get(), resourceUpload, wFilename.c_str(),
			m_texture.ReleaseAndGetAddressOf()));

	m_resourcenum = _RD->m_resourceCount;

	CreateShaderResourceView(_RD->m_d3dDevice.Get(), m_texture.Get(),
		_RD->m_resourceDescriptors->GetCpuHandle(_resourceNum = _RD->m_resourceCount++));

	auto uploadResourcesFinished = resourceUpload.End(_RD->m_commandQueue.Get());


	uploadResourcesFinished.wait();
	
}

Animation2D::~Animation2D()
{
}

void Animation2D::Render(RenderData * _RD, Vector2 _cam_pos, float _zoom, Vector2 _scale,
	Vector2 _pos, int _resourceNum, Color _colour, float _orientation, Vector2 _origin, bool _flipped)
{
	const RECT* r = &RECT(m_spritebox);

	//Vector2 render_scale = _scale * _zoom;

	Vector2 distance_from_origin = _pos - _cam_pos;
	distance_from_origin *= _zoom;

	Vector2 render_pos = ((2 * _zoom) * _cam_pos) + distance_from_origin;

	_origin = Vector2(m_spritebox.width / 2, m_spritebox.height / 2);

	if (_flipped)
	{ 
		_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourcenum),
			GetTextureSize(m_texture.Get()),
			render_pos, r, _colour, _orientation, _origin, _scale,SpriteEffects::SpriteEffects_FlipHorizontally,0);
	}
	else
	{
		_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourcenum),
			GetTextureSize(m_texture.Get()),
			render_pos, r, _colour, _orientation, _origin, _scale);
	}
}

void Animation2D::update(GameStateData * _GSD)
{
	if (play)
	{
		m_elapsedTime += _GSD->m_dt;

		if (m_elapsedTime > 1 / m_framerate)
		{
			m_frames++;
			if (m_frames >= m_maxFrames)
			{
				if (loop)
				{
					reset();
					return;
				}
				else
				{
					play = false;
					return;
				}
			}
			m_spritebox.x += m_spriteBoxIncrements.x;
			XMUINT2 size = GetTextureSize(m_texture.Get());
			if (m_spritebox.x > (size.x - m_spritebox.width))
			{
				m_spritebox.x = m_furthestLeftPos;
				m_spritebox.y += m_spriteBoxIncrements.y;
			}

			m_elapsedTime = 0;
			//m_spritebox.y += m_spriteBoxIncrements.y;
		}
	}
}

void Animation2D::setSpriteBox(Rectangle _box)
{
	m_spritebox = _box;
}

void Animation2D::setFramerate(float _framerate)
{
	m_framerate = _framerate;
}

void Animation2D::setMaxFrames(int _maxFrames)
{
	m_maxFrames = _maxFrames;
}

void Animation2D::setSpriteBoxStartPos(Vector2 _start)
{
	m_spriteBoxStartPos = _start;
}

void Animation2D::setFurthestLeftPos(float _left)
{
	m_furthestLeftPos = _left;
}

void Animation2D::setIncrements(Vector2 _increments)
{
	m_spriteBoxIncrements = _increments;
}

void Animation2D::setloop(bool _loop)
{
	loop = _loop;
}

void Animation2D::setPlay(bool _play)
{
	play = _play;
}

bool Animation2D::getPlay()
{
	return play;
}

const Vector2 Animation2D::getSpriteScale()
{
	Vector2 spriteSize(m_spritebox.width, m_spritebox.height);
	auto desc = m_texture->GetDesc();
	Vector2 textureSize(static_cast<uint32_t>(desc.Width), static_cast<uint32_t>(desc.Height));
	return spriteSize / textureSize;
}

void Animation2D::reset()
{
	m_frames = 0;
	m_elapsedTime = 0;
	m_spritebox.x = m_spriteBoxStartPos.x;
	m_spritebox.y = m_spriteBoxStartPos.y;
	play = true;
}
