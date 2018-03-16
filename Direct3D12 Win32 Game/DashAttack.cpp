#include "pch.h"
#include "DashAttack.h"
#include <fstream>

std::string getFileData(std::ifstream & _file);

DashAttack::DashAttack(std::string _attack_file, RenderData * _RD)
{
	m_RD = _RD;

	std::ifstream attack_file;
	attack_file.open("..\\GameAssets\\Characters\\Attacks\\" + _attack_file);

	m_hold = HOLD_NONE;
	m_data.time = std::stof(getFileData(attack_file));
	m_data.speed = std::stof(getFileData(attack_file));
	m_data.damage = std::stoi(getFileData(attack_file));
	m_data.knockback = std::stoi(getFileData(attack_file));
	m_data.direction.x = std::stof(getFileData(attack_file));
	m_data.direction.y = std::stof(getFileData(attack_file));
	m_data.size.x = std::stoi(getFileData(attack_file));
	m_data.size.y = std::stoi(getFileData(attack_file));

	m_dash_direction.x = std::stof(getFileData(attack_file));
	m_dash_direction.y = std::stof(getFileData(attack_file));
	m_dash_distance = std::stof(getFileData(attack_file));
	attack_file.close();
}

void DashAttack::PerformAttack(Vector2 _position, int _direction, Character * _user, GameStateData * _GSD, SpawnHandler * _spawner, float _charge)
{
	Vector2 relative_dash = Vector2(m_dash_direction.x * _direction, m_dash_direction.y);
	_user->GetPhysics()->ResetForce(BOTH_AXES);
	_user->GetPhysics()->AddForce(relative_dash * m_dash_distance * 1000);

	DamageColData attack = m_data;
	attack.direction.x *= _direction;
	attack.child_to_player = true;
	attack.contact = Destroy::AFTER_TIME;
	attack.user = _user;

	DamageCollider* collider = new DamageCollider(m_RD, attack, _spawner);
	collider->SetPos(_position);
}