#pragma once
#include "Throwable.h"

class MeleeWeapon : public Throwable
{
public:
	MeleeWeapon();
	MeleeWeapon(RenderData* _RD, std::string _filename, SpawnHandler* _spawner);
	MeleeWeapon(Item* item_to_copy, RenderData* _RD, string _filename, SpawnHandler* _spawner); //copy constructor
	~MeleeWeapon();

	void attack(float charged_for, int type);
	void use(Character* char_) override;

	virtual void Tick(GameStateData* _GSD) override;


	float getMaxCharge() { return max_charge; }
	std::string getOnFullCharge() { return on_full_charge; }
	int getDurability() { return durability; }

	void setMaxCharge(float charge_) { max_charge = charge_; }
	void setOnFullCharge(std::string string_) { on_full_charge = string_; }
	void setDurability(int dur) { durability = dur; }


	void CollisionEnter(Physics2D* _collision, Vector2 _normal);
	void Collision(Physics2D* _collision);

private:
	bool m_attacking = false;
	float m_attack_time = 0;

	float max_charge = 0;

	int attack_type = 0;

	std::string on_full_charge = "none";
	float m_charge = 0;
	int durability = 0;

	SpawnHandler* m_spawner = nullptr;
	RenderData* RD_ptr = nullptr;

};

