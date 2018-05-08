#pragma once
#include "ImageGO2D.h"

class TestAnim :
	public ImageGO2D
{
public:
	TestAnim(RenderData * _RD, string _filename);
	~TestAnim();

	void update(GameStateData* _GSD);
	virtual void Render(RenderData* _RD, int _sprite = 0,
		Vector2 _cam_pos = Vector2::Zero, float _zoom = 1) override;
private:
	std::unique_ptr<Animation2D> run = nullptr;
	Vector2 m_scale = Vector2::One;
	Vector2 m_pos = Vector2::Zero;
};

