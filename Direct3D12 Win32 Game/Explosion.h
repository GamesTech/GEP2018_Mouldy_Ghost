#pragma once
#include "ImageGO2D.h"

class Explosion : public ImageGO2D
{
public:
	Explosion() = default;

	/*
	Explosion is a simple collision box that exists for a short amount of time
	collision with the box result in Hit
	radius and power are base on the variables of Explosive that instantiated the explosion
	*/
	Explosion(Vector2 _pos, RenderData* _RD, GameStateData* _GSD, 
		SpawnHandler * _spawner, float _exp_radius, float _power);
	~Explosion();

	virtual void Tick(GameStateData* _GSD);

	virtual void CollisionEnter
	(Physics2D* _collision, Vector2 _normal) override;


protected:
	float m_power = 1;
	SpawnHandler* m_spawner;
	float elapsed_time = 0;
};