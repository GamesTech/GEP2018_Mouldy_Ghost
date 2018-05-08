#pragma once
#include "GameStateData.h"
#include <vector>

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

class Animation2D;
class CharacterActions
{
public:
	CharacterActions() = default;
	~CharacterActions() = default;

	void Tick(GameStateData * _GSD, Character * _character);
	void SetController(CharacterController * _controller, Character * _character);
	void loadAnimations(std::string _file, RenderData * _RD, Character * _character);
	CharacterController* GetController() { return m_controller; }
	
	void setAttacking(bool attacking_) { m_attacking = attacking_; }
	void SetMoveSpeed(float _speed) { m_move_speed = _speed; }
	const float GetMoveSpeed() { return m_move_speed; }
	void SetJumpHeight(float _height) { m_jump_height = _height; }
	const float GetJumpHeight() { return m_jump_height; }
	void SetJumpLimit(int _limit) { m_jump_limit = _limit; }
	const bool canJump() const { return m_jumps < m_jump_limit; }
	const bool getUsesAnim() const { return usesAnimation; }
	Animation2D* getActiveAnim() { return active_anim; }
	const bool isFlipped() const { return flipped; }

	void platformHit();
	void platformLeave();
private:
	int PlayerJump(std::vector<GameAction> _actions, Character * _character);
	int PlayerMove(std::vector<GameAction> _actions, Character * _character);
	void PickUpItem(std::vector<GameAction> _actions, Character * _character);
	void PlayerAttack(GameStateData * _GSD, Character * _character);
	void MeleeAttack(GameStateData * _GSD,
		std::vector<GameAction> _actions, Character * _character);
	void SpecialAttack(GameStateData * _GSD,
		std::vector<GameAction> _actions, Character * _character);
	void MeleeWeaponAttack(GameStateData * _GSD, std::vector<GameAction> _actions, Character * _character);

	//animation variables and functions
	bool usesAnimation = false;
	Animation2D* active_anim = nullptr;
	std::shared_ptr<Animation2D> jump_anim = nullptr;
	std::shared_ptr<Animation2D> run_anim = nullptr;
	std::shared_ptr<Animation2D> idle_anim = nullptr;
	std::shared_ptr<Animation2D> attack_anim = nullptr;
	void switchAnimation(Animation2D* _new);
	void FlipX();
	bool flipped = false;

	CharacterController* m_controller = nullptr;
	bool on_floor = false;
	Item* m_held_item = nullptr;
	Attack* m_charging_attack = nullptr;
	float m_charge_time = 0;
	Attack* m_spamming_attack = nullptr;
	float m_spam_cooldown = 0;
	bool m_attacking = false;
	bool m_dash_recover = true;
	int m_jumps = 1;
	float m_move_speed = 1.0f;
	int m_jump_limit = 2;
	float m_jump_height = 1.0f;
	int m_facing = 1;
};