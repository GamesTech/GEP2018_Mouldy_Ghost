#pragma once
#include "Physics2D.h"

class Platform : public ImageGO2D
{
public:

	/*
	*a collision box with a texture and a "Platofrm" tag
	*_filename specifies the texture that should be loaded
	*/
	Platform(RenderData* _RD, string _filename);
	Platform();
	~Platform();

	virtual void Tick(GameStateData* _GSD);

	void CollisionEnter(Physics2D* _collision, Vector2 _normal) override;
	void Collision(Physics2D* _collision, Vector2 _normal) override;
	void CollisionExit(Physics2D* _collision)override;

private:
};

