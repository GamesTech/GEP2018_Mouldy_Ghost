#include "pch.h" 
#include "MovingPlatform.h"
#include "ImageGO2D.h"
#include "GameStateData.h"
#include "RenderData.h"

/*
platform will be constantly moving between start and end positions
"stay" param indicates how long will the platform stay idling after the goal was reached
*/
MovingPlatform::MovingPlatform(RenderData * _RD, Vector2 _start, Vector2 _end, float _travel_time, float _stay, string _filename) :Platform(_RD, _filename)
{
	start_pos = _start;
	end_pos = _end;

	travel_time = _travel_time;
	stay_time = _stay;
	tag = GameObjectTag::PLATFORM;
}

MovingPlatform::MovingPlatform()
{
}



MovingPlatform::~MovingPlatform()
{
}

void MovingPlatform::Tick(GameStateData * _GSD)
{
	float dt = _GSD->m_dt;

	elapsed_time += dt;

	if (!stay)
	{
		Vector2 newpos = Vector2(0, 0);
		float lerp_value = elapsed_time / travel_time;

		if (direction)
		{
			newpos = Vector2::Lerp(start_pos, end_pos, lerp_value);
		}
		else
		{
			newpos = Vector2::Lerp(end_pos, start_pos, lerp_value);
		}

		if (elapsed_time > travel_time)
		{
			elapsed_time = 0;
			stay = true;

			//set the position to the target position
			//makes sure that the platform never overshoots
			newpos = direction ? end_pos : start_pos;
			direction = !direction;
		}
		m_pos = newpos;
	}
	else
	{
		m_pos = direction ? start_pos : end_pos;
		if (elapsed_time > stay_time)
		{
			elapsed_time = 0;
			stay = false;
		}
	}

	GameObject2D::Tick(_GSD);
	m_physics->Tick(_GSD, m_pos);
}

void MovingPlatform::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	Platform::CollisionEnter(_collision, _normal);

	//parent the object so when the platform moves, the object moves with it
	_collision->GetOwner()->SetParent(this);
	AddChild(_collision->GetOwner());
}

void MovingPlatform::CollisionExit(Physics2D * _collision)
{
	if (_collision->GetOwner()->GetParent() == this)
	{
		Platform::CollisionExit(_collision);
		_collision->GetOwner()->SetParent(nullptr);
		RemoveChild(_collision->GetOwner());
	}
}