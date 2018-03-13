#include "pch.h"
#include "MeleeAttack.h"
#include "GameStateData.h"
#include <fstream>

std::string getFileData(std::ifstream & _file);

MeleeAttack::MeleeAttack(std::string _attack_file)
{
	std::ifstream attack_file;
	attack_file.open("..\\GameAssets\\Characters\\Attacks\\" + _attack_file);

	m_data.time = std::stof(getFileData(attack_file));
	m_data.speed = std::stof(getFileData(attack_file));
	m_data.damage = std::stoi(getFileData(attack_file));
	m_data.knockback = std::stoi(getFileData(attack_file));
	attack_file.close();
}

void MeleeAttack::PerformAttack(int _facing, GameStateData* _GSD)
{
	DamageColData attack = m_data;
	attack.direction.y = 0;
	attack.direction.x = _facing;
	attack.child_to_player = true;
	attack.contact = Destroy::ON_ANYTHING_HIT;
	m_collider = new DamageCollider(attack);
	_GSD->objects_in_scene.push_back(m_collider->GetPhysics());
}
