#pragma once

class Attack;

class Character
{
public:
	Character();
	~Character();

private:
	string m_name;
	ImageGO2D m_sprite;
	ImageGO2D m_icon;

	int m_num_jumps;
	int* m_jump_height;
	float m_mass;
	float m_walk_speed;
	float m_run_speed;

	Attack* attacks;
};