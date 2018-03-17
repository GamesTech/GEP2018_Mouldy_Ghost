#pragma once
#include "ImageGO2D.h"
#include "Events.h"

enum ButtonType {
	SINGLE_EVENT,
	TWO_EVENT
};

class MenuButton :
	public ImageGO2D
{
public:
	MenuButton();
	MenuButton(Event _eventToSend, RenderData * _RD, string _filename);
	MenuButton(Event _leftEventToSend, Event _rightEventToSend, RenderData * _RD, string _filename);
	~MenuButton();
	virtual void Tick(GameStateData* _GSD) override;
	virtual void Render(RenderData * _RD, int _sprite,
		Vector2 _cam_pos = Vector2::Zero) override;
	void setText(std::string _text);

	void setHighlighted(bool _highlighted);
private:
	ButtonType type;
	Event m_eventToSend;
	Event m_eventLeft;
	Event m_eventRight;
	bool m_highlighted;

	Text2D  m_text = Text2D("");
	Vector2 m_textOffset;
};

