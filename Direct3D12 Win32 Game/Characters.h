#pragma once
#include "MeleeAttack.h"

//GEP:: Based on the ImageGO2D a basic keyboard controlled sprite

class CharacterController;

class Character
	: public ImageGO2D
{
public:
	//TODO: add a 3d player and modes to switch between different views and basic physics
	Character(RenderData* _RD, string _filename);
	virtual ~Character();

	virtual void Tick(GameStateData* _GSD);

	void CreatePhysics(RenderData* _RD = nullptr);

	void SetController(CharacterController* _controller)
	{ m_controller = _controller; }

	void SetMoveSpeed(float _speed) { m_move_speed = _speed; }
	const float GetMoveSpeed() { return m_move_speed; }

	void SetJumpHeight(float _height) { m_jump_height = _height; }
	const float GetJumpHeight() { return m_jump_height; }

	void SetLimit(Vector2 _lim) { m_limit = _lim; }
	const Vector2 GetLimit() { return m_limit; }

	void TakeDamage(int _dam) { m_damage += _dam; }
	void ResetDamage() { m_damage = 0; }

	void GetHit(Vector2 _dir, float _force);

	virtual void Collision(Physics2D* _collision) override;

	void AddAttack(MeleeAttack _attack);

protected:
	int m_damage = 0;

	float m_move_speed = 1.0f;
	float m_jump_height = 1.0f;

	Vector2 m_limit;

	CharacterController* m_controller = nullptr;
	std::vector<Attack*> m_attacks;
};