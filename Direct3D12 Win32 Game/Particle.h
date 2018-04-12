#pragma once
#include "GameObject2D.h"
class Particle :
	public ImageGO2D
{
public:
	Particle();
	Particle(Vector2 _origin, std::string _filename, RenderData * _RD);
	~Particle();
	virtual void Tick(GameStateData* _GSD) override;
	void setDestination(Vector2 _destination);
	void setDirection(Vector2 _direction);
	void setSpeed(float _speed);
	void setLifetime(float _lifetime);
	void setSprite(ID3D12Resource* _sprite);
	float getVisibility() { return visibility; }
	bool getDead();
private:

	Vector2 m_origin;
	Vector2 m_destination;
	Vector2 m_direction;
	bool m_dead = false;
	bool m_fade = false;
	float visibility;
	float m_speed;
	float m_lifetime;
	float m_elapsed_time = 0;
};

