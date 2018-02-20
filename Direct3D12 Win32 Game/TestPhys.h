#pragma once
#include "Physics2D.h"

class TestPhys :
	public ImageGO2D
{
public:
	TestPhys(RenderData* _RD, string _filename);
	~TestPhys();

	virtual void Tick(GameStateData* _GSD);

	void CollisionEnter(Physics2D* _collision, Vector2 _normal) override;
	void Collision(Physics2D* _collision) override;
	void CollisionExit(Physics2D* _collision)override;
};