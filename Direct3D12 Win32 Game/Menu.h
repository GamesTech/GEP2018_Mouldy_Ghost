#pragma once
#include "GameObject2D.h"
#include "MenuButton.h"

class MenuButton;

class Menu :
	public GameObject2D
{
public:
	Menu();
	~Menu();

	Menu(Vector2 _pos, MenuButton _first, std::string _firstButtonText);
	void Render(RenderData * _RD, int _sprite,
		Vector2 _cam_pos = Vector2::Zero) override;
	void Tick(GameStateData* _GSD) override;
	void CentreOrigin() override {};
	void addButton(MenuButton _buttonToAdd, std::string _buttonText);
	void init();

	MenuButton* getMenuButton(Event _event);

private:
	Vector2 m_pos;
	Vector2 m_nextButtonPos;
	float m_distanceBetweenButtons;
	std::vector<MenuButton> m_buttons;
	int m_highlighted_index;
};

