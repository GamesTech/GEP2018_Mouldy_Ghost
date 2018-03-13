#include "pch.h"
#include "MeleeAttack.h"
#include <fstream>

MeleeAttack::MeleeAttack(std::string _attack_file)
{
	std::ifstream attack_file;
	attack_file.open("\\GameAssets\\Characers\\Attacks\\" + _attack_file);
	//read time
	//read speed
	//read direction
	//read contact
	//read damage
	//read knockback
	attack_file.close();
}

void MeleeAttack::PerformAttack(int _facing)
{
	DamageColData attack = m_data;
	attack.direction.x *= _facing;
	attack.child_to_player = true;
	m_collider = new DamageCollider(attack);
}
