#pragma once
#include "ImageGO2D.h"

class Explosion : public ImageGO2D
{
public:
	Explosion(Vector2 _pos, RenderData* _RD, GameStateData* _GSD, 
		SpawnHandler * _spawner, float _exp_radius, float _power);
	~Explosion();

	virtual void Tick(GameStateData* _GSD);

	virtual void CollisionEnter
	(Physics2D* _collision, Vector2 _normal) override;


private:

	SpawnHandler* m_spawner;
	float elapsed_time = 0;
};