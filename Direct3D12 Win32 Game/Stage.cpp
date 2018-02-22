#include "pch.h"

#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::update(float dt)
{
}

void Stage::render(RenderData * _RD)
{
	for (auto& object : other_objects)
	{
		object->Render(_RD);
	}

	for (auto& platform : platforms)
	{
		platform->Render(_RD);
	}

}

