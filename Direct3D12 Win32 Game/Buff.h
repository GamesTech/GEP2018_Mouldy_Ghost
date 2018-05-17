#pragma once

enum BuffType
{
	STRENGHT_BUFF

};

class Buff 
{
public:
	//increases or decreases the stats of character that is affected by the buff
	//the stat is then returned to normal when the buff duration expires
	Buff(BuffType _type, Character* _buffed_character, float _power);
	virtual ~Buff();

	bool Tick(GameStateData* _GSD);

private:
	float power;
	Character* m_buffed_character = nullptr;
	BuffType type;
	float duration = 0;
};

