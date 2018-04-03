#include "pch.h"
#include "Emitter.h"
#include <random>


Emitter::Emitter()
{
}

Emitter::Emitter(Vector2 _pos, std::string _file)
{
	SetPos(_pos);
	file = _file;
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

void Emitter::addParticles(int amount, RenderData * _RD)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> random(0, distributionAngle);
	for (int i = 0; i < amount; i++)
	{
		particles.push_back(Particle(GetPos(), file, _RD));

		Vector2 newPointTo(0, 1);
		newPointTo = rotateVector(newPointTo, angle);
		newPointTo = rotateVector(newPointTo, distributionAngle / -2);
		newPointTo = rotateVector(newPointTo, random(mt));
		particles.back().setDestination(newPointTo);

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
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].Render(_RD, _sprite, _cam_pos, _zoom);
	}
}
