#pragma once
#include "StandardAttack.h"
#include "DashAttack.h"
#include "InputSystem.h"
#include "CharacterController.h"
#include "Buff.h"
#include "Emitter.h"

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

class SpawnHandler;
class Item;
class Animation2D;

class Character
	: public ImageGO2D
{
public:
	//TODO: add a 3d player and modes to switch between different views and basic physics
	Character(RenderData* _RD, string _filename);
	virtual ~Character();
	virtual void Tick(GameStateData* _GSD);
	virtual void Render(RenderData* _RD, int _sprite = 0,
		Vector2 _cam_pos = Vector2::Zero, float _zoom = 1) override;

	void CreatePhysics(RenderData* _RD = nullptr);

	void SetController(CharacterController* _controller);
	const int GetControllerIndex() { return m_controller->GetControllerID(); }

	void SetMoveSpeed(float _speed) { m_move_speed = _speed; }
	const float GetMoveSpeed() { return m_move_speed; }

	void SetJumpHeight(float _height) { m_jump_height = _height; }
	const float GetJumpHeight() { return m_jump_height; }
	void SetJumpLimit(int _limit) { m_jump_limit = _limit; }
	const bool canJump() const { return m_jumps < m_jump_limit; }

	int GetStrenght() { return strenght; }
	void SetStrenght(int _str) { strenght = _str; }

	void BuffCharacter(Buff* _buff);

	void loadAnimations(std::string _file, RenderData* _RD);

	void TakeDamage(int _dam);
	void Hit(Vector2 _dir, float _force, Character * _attacker);
	const int GetDamage() { return m_damage; }
	void ResetDamage() { m_damage = 0; }

	void LoseLife() { m_lives--; }
	void ResetLives() { m_lives = 3; }
	const int GetLives() { return m_lives; }
	void SetLives(int _set) { m_lives = _set; }
	void setinfinitelives(bool _set) { m_infiniteLives = _set; }

	virtual void CollisionEnter(Physics2D* _collision, Vector2 _normal) override;
	virtual void CollisionExit(Physics2D* _collision) override;
	virtual void Collision(Physics2D* _collision, Vector2 _normal) override;

	void AddAttack(StandardAttack _attack);
	void AddAttack(DashAttack _attack);

	void AddPoints(int _add) { m_points += _add; }
	const int GetPoints() { return m_points; }
	const Color getTextColour() const;
	void setTextColour(Color colour);

	void setAttacking(bool attacking_) { m_attacking = attacking_; }

protected:

	int PlayerJump(std::vector<GameAction> _actions);
	int PlayerMove(std::vector<GameAction> _actions);
	void PickUpItem(std::vector<GameAction> _actions);
	void PlayerAttack(GameStateData * _GSD);
	void MeleeAttack(GameStateData * _GSD,
		std::vector<GameAction> _actions);
	void SpecialAttack(GameStateData * _GSD,
		std::vector<GameAction> _actions);
	void MeleeWeaponAttack(GameStateData * _GSD,
		std::vector<GameAction> _actions);

	//animation variables and functions
	bool usesAnimation = false;
	Animation2D* active_anim = nullptr;
	std::shared_ptr<Animation2D> jump_anim = nullptr;
	std::shared_ptr<Animation2D> run_anim = nullptr;
	std::shared_ptr<Animation2D> idle_anim = nullptr;
	std::shared_ptr<Animation2D> attack_anim = nullptr;
	void switchAnimation(Animation2D* _new);
	bool on_floor = false;

	Emitter m_damage_emitter;
	std::shared_ptr<Emitter> m_die_emitter = nullptr;

	float m_recovery_time = 0;
	int m_jumps = 1;
	int m_damage = 0;
	int m_lives = 3;
	int strenght = 0;
	bool m_infiniteLives = false;
	float m_move_speed = 1.0f;
	int m_jump_limit = 2;
	float m_jump_height = 1.0f;
	int m_facing = 1;
	CharacterController* m_controller = nullptr;
	std::vector<Attack*> m_attacks;
	Attack* m_charging_attack = nullptr;
	float m_charge_time = 0;
	Attack* m_spamming_attack = nullptr;
	float m_spam_cooldown = 0;
	bool m_attacking = false;
	bool m_dash_recover = true;
	Rectangle m_death_zone = Rectangle(-500,-500, 1700, 1400);
	Character* m_last_to_hit = nullptr;//The last player to hit this player, used for scoring in time matches
	int m_points = 0;
	Item* m_held_item = nullptr;
	Color m_text_colour;
	std::vector<Buff*> buffs;
};