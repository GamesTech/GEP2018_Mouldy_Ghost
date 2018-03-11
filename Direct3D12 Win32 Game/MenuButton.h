#pragma once
#include "ImageGO2D.h"
#include "Events.h"
class MenuButton :
	public ImageGO2D
{
public:
	MenuButton();
	MenuButton(Event _eventToSend, RenderData * _RD, string _filename);
	~MenuButton();
	virtual void Tick(GameStateData* _GSD) override;
	virtual void Render(RenderData * _RD, int _sprite) override;
	void setText(std::string _text);

	void setHighlighted(bool _highlighted);
private:
	Event m_eventToSend;
	bool m_highlighted;

	Text2D  m_text = Text2D("");
	Vector2 m_textOffset;
};

