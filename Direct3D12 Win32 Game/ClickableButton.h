#pragma once
#include "ImageGO2D.h"
#include "Events.h"

class Cursor;
class ClickableButton
	: public ImageGO2D
{
public:
	ClickableButton(RenderData* _RD, string _filename, std::string _text, Event _return_scene, Vector2 _position, Vector2 _scale);
	~ClickableButton() = default;

	void Render(RenderData* _RD, int _sprite = 0,
		Vector2 _cam_pos = Vector2::Zero, float _zoom = 1) override;
	void setText(std::string _text);
	Event* mouseUpdate(Cursor* _cursor, GameStateData* _GSD);
private:
	Text2D text = Text2D("");
	Rectangle bounds;
	Event return_scene;
};