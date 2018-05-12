#pragma once

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
	Character * user;      //player attacking
	bool child_to_player;  //should be childed to attacking player
	float time;            //how long the attack will exist before despawning
	float speed;           //speed at which the attack moves
	Vector2 direction;     //direction of the attack
	Destroy contact;       //how does the attack despawn
	int damage;            //how much damage
	int knockback;         //how much knockback
	Vector2 size;          //how big is the projectile
	bool grav;             //is the projectile affected by gravity
	std::string file;      //which sprite should the projectile use?
};