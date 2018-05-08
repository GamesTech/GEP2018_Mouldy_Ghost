#pragma once
#include "pch.h"
#include "Platform.h"


class MovingPlatform :public Platform
{
public:
	
	MovingPlatform(RenderData* _RD, Vector2 _start, Vector2 _end, float _travel_time, float _stay, string _filename);
	MovingPlatform();
	~MovingPlatform();

	void Tick(GameStateData* _GSD) override;

	virtual void CollisionEnter(Physics2D* _collision, Vector2 _normal) override;

	virtual void CollisionExit(Physics2D * _collision) override;

private:
	Vector2 start_pos;
	Vector2 end_pos;
	float travel_time = 1;
	float stay_time = 3;

	float elapsed_time = 0;

	bool direction = true; /*
	true: start->end
	 false: end->start*/

	bool stay = false;
};

