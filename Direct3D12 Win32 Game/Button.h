#pragma once
#include "ImageGO2D.h"

class Button
	: public ImageGO2D
{
public:
	Button(RenderData* _RD, string _filename, std::string _text, Vector2 _position, Vector2 _scale);
	~Button() = default;

	void setText(std::string _text);
	virtual void Render(RenderData * _RD);
	virtual void mouseUpdate(GameStateData* _GSD) = 0;
protected:
	Text2D text = Text2D("");
	Rectangle m_bounds;
};