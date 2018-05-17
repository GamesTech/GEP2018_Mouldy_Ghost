#include "pch.h"
#include "StandardAttack.h"
#include "GameStateData.h"
#include "SpawnHandler.h"
#include <fstream>

std::string getFileData(std::ifstream & _file);

StandardAttack::StandardAttack(std::string _attack_file, RenderData* _RD)
{
	m_RD = _RD;

	std::ifstream attack_file;
	attack_file.open("..\\GameAssets\\Characters\\Attacks\\" + _attack_file);

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

	m_hold_val = std::stof(getFileData(attack_file));
	if(m_hold_val == 0)
		m_hold = HOLD_NONE;
	if(m_hold_val < 0)
		m_hold = HOLD_REPEAT;
	if(m_hold_val > 0)
		m_hold = HOLD_CHARGE;

	m_data.time = std::stof(getFileData(attack_file));
	m_data.speed = std::stof(getFileData(attack_file));
	m_data.damage = std::stoi(getFileData(attack_file));
	m_data.knockback = std::stoi(getFileData(attack_file));
	m_data.direction.x = std::stoi(getFileData(attack_file));
	m_data.direction.y = std::stoi(getFileData(attack_file));
	m_data.size.x = std::stoi(getFileData(attack_file));
	m_data.size.y = std::stoi(getFileData(attack_file));
	m_data.grav = getFileData(attack_file)[0] == 't';
	m_data.file = getFileData(attack_file);

	attack_file.close();
}

void StandardAttack::PerformAttack(Vector2 _position, int _direction,
	Character* _user, GameStateData* _GSD, 
	SpawnHandler* _spawner, float _charge)
{
	if (m_hold == HOLD_CHARGE)
	{
		_charge = _charge > m_hold_val ? m_hold_val : _charge;
	}

	DamageColData attack = m_data;

	attack.damage += _user->GetStrenght();
	attack.damage *= (1 + _charge);
	attack.knockback *= (1 + _charge);

	attack.direction.x *= _direction;
	attack.child_to_player = true;
	attack.user = _user;

	DamageCollider* newcol = new DamageCollider(m_RD, attack, _spawner);
	newcol->SetPos(_position);
	_spawner->onNotify(newcol, Event::OBJECT_INSTANTIATED);
}