#include "pch.h"
#include "Buff.h"
#include "GameStateData.h"




Buff::Buff(BuffType _type, Character* _buffed_character, float _power)
{
	m_buffed_character = _buffed_character;

	type = _type;
	power = _power;

	if (type == BuffType::STRENGHT_BUFF)
	{
		m_buffed_character->SetStrenght(m_buffed_character->GetStrenght() + power);
	}

	
}

Buff::~Buff()
{

	if (type == BuffType::STRENGHT_BUFF)
	{
		m_buffed_character->SetStrenght(m_buffed_character->GetStrenght() - power);
	}
}

bool Buff::Tick(GameStateData * _GSD)
{
	duration += _GSD->m_dt;

	if (duration > 10)
	{
		//returning gives signal to the buffed character to delete this buff
		//destructor will be called and affeted stat will return to normal
		return true;
	}

	return false;
}
