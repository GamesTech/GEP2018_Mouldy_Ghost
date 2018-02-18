#pragma once

#include "pch.h"

//GEP:: Based on the ImageGO2D a basic keyboard controlled sprite

class Player2D
	: public ImageGO2D
{
public:

	//TODO: add a 3d player and modes to switch between different views and basic physics
	Player2D(RenderData* _RD, string _filename);
	virtual ~Player2D();

	virtual void Tick(GameStateData* _GSD);

	void SetDrive(float _drive) { m_drive = _drive; }
	const float GetDrive() { return m_drive; }

	void SetLimit(Vector2 _lim) { m_limit = _lim; }
	const Vector2 GetLimit() { return m_limit; }

	void SetMoveSpeed(float _speed) { m_move_speed = _speed; }
	const float GetMoveSpeed() { return m_move_speed; }

	void SetJumpHeight(float _height) { m_jump_height = _height; }
	const float GetJumpHeight() { return m_jump_height; }

	void SetControllerID(int _ID) { m_controllerID = _ID; }
	const int GetControllerID() { return m_controllerID; }

	virtual void Collision(Physics2D* _collision) override;

protected:
	float m_drive = 1.0f;
	float m_move_speed = 1.0f;
	float m_jump_height = 1.0f;

	int m_controllerID = 0;

	Vector2 m_limit;
};