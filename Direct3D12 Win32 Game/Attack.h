#pragma once
#include <string>

enum AttackType
{
	ATK_RANGED,			//Standard and non-standard attacks that spawn projectiles
	ATK_MELEE,			//Standard and non-standard attacks that spawn a short-range damage object
	ATK_COUNTER,		//Counter move
	ATK_GRAB,			//It's a grab
	ATK_PASSIVE,		//Has an effect which doesn't necessarily affect other players
};

enum OnHold
{
	HOLD_CHARGE,		//Changes the attack when the button is held
	HOLD_REPEAT,		//Repeats the attack until the button is released
	HOLD_NONE			//Attacks once and holding the button will make the player just stand there
};

class Attack
{
public:
	Attack(std::string _attack_file);
	~Attack() = default;

	virtual void SetUpAttack(std::string _attack_file);

private:
};