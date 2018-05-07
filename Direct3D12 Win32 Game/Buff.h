#pragma once

enum BuffType
{
	STRENGHT_BUFF

};

class Buff 
{
public:
	Buff(BuffType _type, Character* _buffed_character, float _power);
	virtual ~Buff();

	bool Tick(GameStateData* _GSD);

private:
	float power;
	Character* m_buffed_character = nullptr;
	BuffType type;
	float duration = 10;
};

