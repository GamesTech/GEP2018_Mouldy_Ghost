#pragma once
#include "StandardAttack.h"
#include "DashAttack.h"
#include "InputSystem.h"
#include "CharacterController.h"
#include "CharacterActions.h"
#include "Buff.h"

//GEP:: Based on the ImageGO2D a basic keyboard controlled sprite

class SpawnHandler;
class Item;
class Animation2D;
class Emitter;

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

	int GetStrenght() { return strenght; }
	void SetStrenght(int _str) { strenght = _str; }

	void BuffCharacter(Buff* _buff);

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
	Attack* GetAttack(int index) { return m_attacks[index]; };

	void AddPoints(int _add) { m_points += _add; }
	const int GetPoints() { return m_points; }
	const Color getTextColour() const;
	void setTextColour(Color colour);
	SpawnHandler* findSpawnHandler();
	int getResourceNum() const { return m_resourceNum; }
	CharacterActions* getActions() { return m_actions.get(); }
	void setMovement(float speed, int jumps, int height);
protected:
	std::shared_ptr<Emitter> m_damage_emitter = nullptr;
	std::shared_ptr<Emitter> m_die_emitter = nullptr;
	float m_recovery_time = 0;
	int m_damage = 0;
	int m_lives = 3;
	int strenght = 0;
	bool m_infiniteLives = false;
	std::vector<Attack*> m_attacks;
	Rectangle m_death_zone = Rectangle(-500,-500, 1700, 1400);
	Character* m_last_to_hit = nullptr;//The last player to hit this player, used for scoring in time matches
	int m_points = 0;
	Color m_text_colour;
	std::vector<Buff*> buffs;
	std::shared_ptr<CharacterActions> m_actions;
};