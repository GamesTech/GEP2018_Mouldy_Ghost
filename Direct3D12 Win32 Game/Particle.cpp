#include "pch.h"
#include "Particle.h"
#include "GameStateData.h"


Particle::Particle()
{
}

Particle::Particle(Vector2 _origin, std::string _filename, RenderData * _RD) : ImageGO2D(_RD, _filename)
{
	m_origin = _origin;
	SetPos(m_origin);
}


Particle::~Particle()
{
}

void Particle::Tick(GameStateData * _GSD)
{
	//do stuff
	//need to find out what delta time is stored as (seconds? milliseconds?)
	m_elapsed_time += _GSD->m_dt;
	SetPos(GetPos() + ((m_direction * (m_speed * - 1)) * _GSD->m_dt));
	if (m_fade)
	{
		float visibility = m_elapsed_time / m_lifetime;
		visibility = 255 - (visibility * 255);
		//sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, (visibility)));
	}
	if (m_elapsed_time > m_lifetime)
	{
		m_dead = true;
	}
}

void Particle::setDestination(Vector2 _destination)
{
	m_destination = _destination;
	m_direction = GetPos() - m_destination;
	//normalize move vector
	float length = sqrt((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y));
	m_direction = Vector2(m_direction.x / length, m_direction.y / length);
}

void Particle::setSpeed(float _speed)
{
	m_speed = _speed;
}

void Particle::setLifetime(float _lifetime)
{
	m_lifetime = _lifetime;
}

bool Particle::getDead()
{
	return m_dead;
}

