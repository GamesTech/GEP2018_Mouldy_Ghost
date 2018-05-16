#include "pch.h"
#include "CharacterBuilder.h"
#include "RenderData.h"

void CharacterBuilder::Initialise(RenderData * _RD,
	GameStateData * _GSD, int _outputWidth,
	int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	Scene::Initialise(_RD, _GSD, _outputWidth, _outputHeight, _audEngine);

	m_menu_switch.intervals = 1;
	m_menu_switch.value = 0;
	m_menu_switch.down = ClickableButton
	(_RD, "button", "<", Event::CHARACTER_CREATION_PAGE_PREV,
		Vector2(10, 1), Vector2(0.1, 0.1));
	m_menu_switch.up = ClickableButton
	(_RD, "button", "<", Event::CHARACTER_CREATION_PAGE_NEXT,
		Vector2(210, 1), Vector2(0.1, 0.1));

	for (int i = 0; i < attack_count; i++)
	{
		m_hold_num[i].intervals = 0.1f;
		m_hold_num[i].value = 0;
		m_hold_num[i].down = ClickableButton
		(_RD, "button", "<", Event::CHARACTER_CREATION_HOLD_DOWN,
			Vector2(10, 100), Vector2(0.1, 0.1));
		m_hold_num[i].up = ClickableButton
		(_RD, "button", "<", Event::CHARACTER_CREATION_HOLD_UP,
			Vector2(10, 100), Vector2(0.1, 0.1));

		m_despawn[i].intervals = 0.1f;
		m_despawn[i].value = 1;

		m_speed[i].intervals = 5;
		m_speed[i].value = 50;

		m_damage[i].intervals = 1;
		m_damage[i].value = 5;

		m_knockback[i].intervals = 1;
		m_knockback[i].value = 20;

		m_dir_x[i].intervals = 0.1f;
		m_dir_x[i].value = 1;

		m_dir_y[i].intervals = 0.1f;
		m_dir_y[i].value = 0;

		m_size_y[i].intervals = 5;
		m_size_y[i].value = 20;

		m_size_x[i].intervals = 5;
		m_size_x[i].value = 20;
	}

}