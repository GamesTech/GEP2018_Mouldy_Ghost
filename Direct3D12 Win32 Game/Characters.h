#pragma once
#include "MeleeAttack.h"
#include "InputSystem.h"

//GEP:: Based on the ImageGO2D a basic keyboard controlled sprite

enum AttackMap
{
	BASIC_BASIC,
	SIDE_BASIC,
	UP_BASIC,
	DOWN_BASIC,

	BASIC_SPECIAL,
	SIDE_SPECIAL,
	UP_SPECIAL,
	DOWN_SPECIAL,

	GRAB,
	FORWARD_THROW,
	BACK_THROW,
	UP_THROW,
	DOWN_THROW
};

class CharacterController;
class SpawnHandler;

class Character
	: public ImageGO2D
{
public:
	//TODO: add a 3d player and modes to switch between different views and basic physics
	Character(RenderData* _RD, string _filename, SpawnHandler* _spawner);
	virtual ~Character();

	virtual void Tick(GameStateData* _GSD);

	void CreatePhysics(RenderData* _RD = nullptr);

	void SetController(CharacterController* _controller)
	{ m_controller = _controller; }

	void SetMoveSpeed(float _speed) { m_move_speed = _speed; }
	const float GetMoveSpeed() { return m_move_speed; }

	void SetJumpHeight(float _height) { m_jump_height = _height; }
	const float GetJumpHeight() { return m_jump_height; }

	void TakeDamage(int _dam) { m_damage += _dam; }
	void ResetDamage() { m_damage = 0; }

	void GetHit(Vector2 _dir, float _force);

	virtual void Collision(Physics2D* _collision) override;

	void AddAttack(MeleeAttack _attack);

protected:
	int PlayerJump(std::vector<GameAction> _actions);
	int PlayerMove(std::vector<GameAction> _actions);
	void PlayerAttack(GameStateData * _GSD);

	float m_recovery_time = 0;

	int m_jumps = 1;

	int m_damage = 0;

	float m_move_speed = 1.0f;
	float m_jump_height = 1.0f;

	int m_facing = 1;

	CharacterController* m_controller = nullptr;
	std::vector<Attack*> m_attacks;
	Attack* m_charging_attack = nullptr;
	float m_charge_time = 0;
	Attack* m_spamming_attack = nullptr;
	float m_spam_cooldown = 0;
	bool m_can_attack = true;
	SpawnHandler* m_spawner;

	Rectangle m_death_zone = Rectangle(-500,-500, 0, 0);
};