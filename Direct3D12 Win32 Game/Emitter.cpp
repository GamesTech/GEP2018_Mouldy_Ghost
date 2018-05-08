#include "pch.h"
#include "Emitter.h"
#include "RenderData.h"
#include "GameStateData.h"
#include <random>


Emitter::Emitter()
{
}

Emitter::Emitter(Vector2 _pos, std::string _file, RenderData * _RD)
{
	bool texture_found = false;
	for (int i = 0; i < allTextures.size(); i++)
	{
		if (allTextures[i].textureName == _file)
		{
			texture_found = true;
			m_textureIndex = i;
			m_resourceNum = allTextures[i].resource_num;
		}
	}

	if (!texture_found)
	{
		TextureItem temp;
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		string fullpath = "../DDS/" + _file + ".dds";
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

		temp.textureName = _file;
		temp.resource_num = m_resourceNum;
		allTextures.push_back(temp);
	}

	m_spriteSize = Vector2(GetTextureSize
	(allTextures[m_textureIndex].texture.Get()).x,
	GetTextureSize(allTextures[m_textureIndex].texture.Get()).y);
	CentreOrigin();


	particles.reserve(100);
	SetPos(_pos);
	file = _file;
	RD = _RD;
}


Emitter::~Emitter()
{
}

void Emitter::setSpeeds(float _min, float _max)
{
	//if min and max are the wrong way round, flip them.
	if (_min < _max)
	{
		minSpeed = _min;
		maxSpeed = _max;
	}
	else
	{
		minSpeed = _max;
		maxSpeed = _min;
	}
}

void Emitter::setRate(float _rate)
{
	spawnRate = _rate;
}

void Emitter::setLifetimes(float _min, float _max)
{
	//if min and max are the wrong way round, flip them.
	if (_min < _max)
	{
		minLifetime = _min;
		maxLifetime = _max;
	}
	else
	{
		minLifetime = _max;
		maxLifetime = _min;
	}
}

void Emitter::setAngle(float _angle)
{
	angle = _angle;
}

void Emitter::setDistribution(float _angle)
{
	distributionAngle = _angle;
}

void Emitter::addParticles(int amount)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> random(0, distributionAngle);
	for (int i = 0; i < amount; i++)
	{
		particles.push_back(Particle(GetPos(), file, RD));
		particles.back().setSprite(allTextures[m_textureIndex].texture.Get());
		Vector2 newPointTo(0, 1);
		newPointTo = rotateVector(newPointTo, angle);
		newPointTo = rotateVector(newPointTo, distributionAngle / -2);
		newPointTo = rotateVector(newPointTo, random(mt));
		//particles.back().setDestination(newPointTo);
		particles.back().setDirection(newPointTo);

		std::random_device rd2;
		std::mt19937 mt2(rd2());
		std::uniform_real_distribution<float> random2(minSpeed, maxSpeed);
		float inputSpeed = random2(mt2);
		particles.back().setSpeed(inputSpeed);

		std::random_device rd3;
		std::mt19937 mt3(rd3());
		std::uniform_real_distribution<float> random3(minLifetime, maxLifetime);
		float inputLifetime = random3(mt3);
		particles.back().setLifetime(inputLifetime);
	}
}

Vector2 Emitter::rotateVector(Vector2 _vector, double _angle)
{
	Vector2 newVector;
	double cs = cos(_angle);
	double sn = sin(_angle);

	newVector.x = _vector.x * cs - _vector.y * sn;
	newVector.y = _vector.x * sn + _vector.y * cs;
	return newVector;
}

void Emitter::CentreOrigin()
{
	//do nothing
}

void Emitter::Tick(GameStateData * _GSD)
{
	elapsedTime += _GSD->m_dt;

	if (spawnRate > 0 && elapsedTime > (1 / spawnRate))
	{
		addParticles(elapsedTime / (1 / spawnRate));
		elapsedTime = 0;
	}

	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].Tick(_GSD);
		if (particles[i].getDead())
		{
			particles.erase(particles.begin() + i);
			i--;
		}
	}
	if (particles.size() == 0)
	{
		empty = true;
	}
	else
	{
		empty = false;
	}
}

void Emitter::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom)
{
	Rectangle rect = Rectangle(0, 0, m_spriteSize.x, m_spriteSize.y);
	const RECT* r = &RECT(rect);

	Vector2 render_scale = m_scale * _zoom;
	

	for (int i = 0; i < particles.size(); i++)
	{
	Vector2 distance_from_origin = particles[i].GetPos() - _cam_pos;
	distance_from_origin *= _zoom;

	Vector2 render_pos = ((2 * _zoom) * _cam_pos) + distance_from_origin;

	m_colour.A(particles[i].getVisibility());

	_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
		GetTextureSize(allTextures[m_textureIndex].texture.Get()),
		render_pos, r, m_colour, m_orientation, m_origin, render_scale);


		//particles[i].Render(_RD, _sprite, _cam_pos, _zoom);
	}
}
