#include "pch.h"
#include "TestAnim.h"
#include "Animation2D.h"


TestAnim::TestAnim(RenderData * _RD, string _filename)
	: ImageGO2D(_RD, _filename)
{
	run = std::make_unique<Animation2D>(_RD, _filename, m_resourceNum);
	//hard coding some stuff for testing. this needs to change
	run->setFramerate(30);
	run->setSpriteBox(Rectangle(0, 0, 160, 290));
	run->setSpriteBoxStartPos(Vector2(0, 0));
	run->setIncrements(Vector2(165, 293));
	run->setMaxFrames(28);
	m_pos = Vector2(500, 300);
	m_origin = Vector2::Zero;
}

TestAnim::~TestAnim()
{
}

void TestAnim::update(GameStateData * _GSD)
{
	run->update(_GSD);
}

void TestAnim::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom)
{
	run->Render(_RD, _cam_pos, _zoom, m_scale, m_pos, m_resourceNum, m_colour, m_orientation, m_origin);
}
