#pragma once
#if _DEBUG
#include "Scene.h"
#include "InputTextBox.h"
#include "ClickableButton.h"

const int attack_count = 8;

struct NumberButton
{
	ClickableButton down;
	ClickableButton up;
	float value;
	float intervals;
};

struct StringButton
{
	ClickableButton prev;
	ClickableButton next;
	std::string value;
};

class CharacterBuilder
	: public Scene
{
public:
	CharacterBuilder() = default;
	~CharacterBuilder() = default;
	std::string getType() { return "CharacterBuilder"; }
	void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
	void Reset() {}
private:
	enum class Screen
	{
		IMAGES = -2,
		MOVEMENT,
		BASIC_A,
		SIDE_A,
		UP_A,
		DOWN_A,
		BASIC_X,
		SIDE_X,
		UP_X,
		DOWN_X,
	};

	Screen m_active_screen = Screen::IMAGES;
	NumberButton m_menu_switch;

	InputTextBox m_name;
	InputTextBox m_image;
	InputTextBox m_animations;

	InputTextBox m_attack_name[attack_count];
	StringButton m_destroy[attack_count];
	StringButton m_hold[attack_count];
	NumberButton m_hold_num[attack_count];
	NumberButton m_despawn[attack_count];
	NumberButton m_speed[attack_count];
	NumberButton m_damage[attack_count];
	NumberButton m_knockback[attack_count];
	NumberButton m_dir_x[attack_count];
	NumberButton m_dir_y[attack_count];
	NumberButton m_size_x[attack_count];
	NumberButton m_size_y[attack_count];
	StringButton m_grav[attack_count];
	StringButton m_sprite[attack_count];
};
#endif