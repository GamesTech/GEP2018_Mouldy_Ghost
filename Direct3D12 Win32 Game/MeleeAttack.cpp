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

void MeleeAttack::PerformAttack(Vector2 _position, int _facing,
	Character* _user, GameStateData* _GSD)
{
	DamageColData attack = m_data;
	attack.direction.y = 0;
	attack.direction.x = _facing;
	attack.child_to_player = true;
	attack.contact = Destroy::ON_ANYTHING_HIT;
	attack.user = _user;

	m_collider = new DamageCollider(attack);
	m_collider->SetPos(_position);
	
	_GSD->m_2DObjects.push_back(m_collider);
	_GSD->objects_in_scene.push_back(m_collider->GetPhysics());
}
