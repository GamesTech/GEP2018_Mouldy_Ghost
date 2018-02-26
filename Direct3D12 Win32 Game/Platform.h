#pragma once
#include "Physics2D.h"

class Platform : public ImageGO2D
{
public:
	//using Physics2D::Physics2D;
	Platform(RenderData* _RD, string _filename);
	Platform();
	~Platform();

	virtual void Tick(GameStateData* _GSD);

	void CollisionEnter(Physics2D* _collision, Vector2 _normal) override;
	void Collision(Physics2D* _collision) override;
	void CollisionExit(Physics2D* _collision)override;

private:
};

