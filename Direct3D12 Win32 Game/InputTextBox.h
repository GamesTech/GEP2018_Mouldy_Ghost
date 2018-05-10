#pragma once
#include "Button.h"

class InputTextBox
	: public Button
{
public:
	InputTextBox(RenderData* _RD, Vector2 _pos);
	~InputTextBox() = default;


	void CentreOrigin() override;
	void Tick(GameStateData* _GSD) override;
	void Render(RenderData* _RD) override;
	void mouseUpdate(GameStateData* _GSD);

private:
	void updateContents();
	bool keyPress(Keyboard::Keys _key, GameStateData* _GSD);

	Rectangle m_bounds;
	bool m_selected;
	std::vector<char> m_text_in_box;
	std::unique_ptr<Text2D> m_contents;
};