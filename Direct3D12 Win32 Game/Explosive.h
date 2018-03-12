#pragma once
#include "Throwable.h"

class Explosive : public Throwable
{
public:
	Explosive();
	~Explosive();

	virtual void Tick(GameStateData* _GSD);

	void CollisionEnter(Physics2D* _collision, Vector2 _normal) override;
	//void Collision(Physics2D* _collision);
	

private:
	
	bool m_explode = false;
	float m_fuse = 0;
	float m_explosion_range = 5;
};


