#pragma once

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

enum Destroy
{
	ON_PLAYER_HIT,
	ON_ANYTHING_HIT,
	AFTER_TIME
};

class Character;
struct DamageColData
{
	Character * user;
	bool child_to_player;
	float time;
	float speed;
	Vector2 direction;
	Destroy contact;
	int damage;
	int knockback;
};