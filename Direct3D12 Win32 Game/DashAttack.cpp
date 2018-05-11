#include "pch.h"
#include "DashAttack.h"
#include "SpawnHandler.h"
#include <fstream>

std::string getFileData(std::ifstream & _file);

DashAttack::DashAttack(std::string _attack_file, RenderData * _RD)
{
	m_RD = _RD;

	std::ifstream attack_file;
	attack_file.open("..\\GameAssets\\Characters\\Attacks\\" + _attack_file);

	m_hold = HOLD_NONE;

	std::string destroy = getFileData(attack_file);
	switch (destroy[0])
	{
	case 'a':
	case 'A':
		m_data.contact = Destroy::ON_ANYTHING_HIT;
		break;
	case 'p':
	case 'P':
		m_data.contact = Destroy::ON_PLAYER_HIT;
		break;
	case 'n':
	case 'N':
		m_data.contact = Destroy::AFTER_TIME;
		break;
	}

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

	m_data.grav = getFileData(attack_file)[0] == 't';
	m_data.file = getFileData(attack_file);
	attack_file.close();
}

void DashAttack::PerformAttack(Vector2 _position, int _direction, Character * _user, GameStateData * _GSD, SpawnHandler * _spawner, float _charge)
{
	Vector2 relative_dash = Vector2(m_dash_direction.x * _direction, m_dash_direction.y);
	_user->GetPhysics()->ResetForce(BOTH_AXES);
	_user->GetPhysics()->AddForce(relative_dash * m_dash_distance * 1000);


	DamageColData attack = m_data;
	attack.damage += _user->GetStrenght();
	attack.direction.x *= _direction;
	attack.child_to_player = true;
	attack.user = _user;

	DamageCollider* collider = new DamageCollider(m_RD, attack, _spawner);
	collider->SetPos(_position);
	_spawner->onNotify(collider, Event::OBJECT_INSTANTIATED);
}