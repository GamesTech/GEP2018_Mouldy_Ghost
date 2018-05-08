#include "pch.h"

#include "FinalDestination.h"
#include "GameStateData.h"

FinalDestination::FinalDestination()
{
}

FinalDestination::~FinalDestination()
{
	for (auto& platform : platforms)
	{
		delete platform;
		platform = nullptr;
	}

	platforms.clear();
}

void FinalDestination::update(GameStateData* _GSD)
{
	for (auto& platform : platforms)
	{
		platform->Tick(_GSD);
	}

}

void FinalDestination::init(RenderData* _RD, GameStateData * _GSD)
{
	Platform* testplatform = new Platform(_RD, "platform");

	testplatform->SetSpawn(Vector2(400, 400));

	testplatform->SetScale(Vector2(2, 1));
	Rectangle rect = Rectangle
	(testplatform->GetPos().x, testplatform->GetPos().y,
		testplatform->TextureSize().x * 2,
		testplatform->TextureSize().y );

	

	testplatform->GetPhysics()->SetCollider(rect);

	platforms.push_back(testplatform);
	_GSD->objects_in_scene.push_back(testplatform->GetPhysics());

	spawn[0] = Vector2(-100, 100);
	spawn[1] = Vector2(150, 100);
	spawn[2] = Vector2(400, 100);
	spawn[3] = Vector2(650, 100);
}
