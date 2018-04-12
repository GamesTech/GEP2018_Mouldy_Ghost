#pragma once
#include "Throwable.h"

class Explosive : public Throwable
{
public:
	Explosive();
	Explosive(RenderData* _RD, std::string _filename, SpawnHandler* _spawner);
	Explosive(Item* item_to_copy, RenderData* _RD, string _filename, SpawnHandler* _spawner); //copy constructor
	~Explosive();

	virtual void Tick(GameStateData* _GSD);

	void CollisionEnter(Physics2D* _collision, Vector2 _normal) override;
	//void Collision(Physics2D* _collision);
	
	void setFuse(float _fuse) { m_fuse = _fuse; }
	void setExpRange(float _range) { m_explosion_range = _range; }

	float getFuse() { return m_fuse; }
	float getExpRange() { return m_explosion_range;}
private:
	RenderData* RD_ptr;

	bool m_explode = false;
	float m_fuse = 0;
	float m_explosion_range = 5;
};


