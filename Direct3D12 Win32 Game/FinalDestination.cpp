#include "pch.h"

#include "FinalDestination.h"
#include "GameStateData.h"

FinalDestination::FinalDestination()
{
}

FinalDestination::~FinalDestination()
{
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

	testplatform->SetSpawn(Vector2(600, 400));

	Rectangle rect = Rectangle
	(testplatform->GetPos().x, testplatform->GetPos().y,
		testplatform->TextureSize().x,
		testplatform->TextureSize().y);

	testplatform->GetPhysics()->SetCollider(rect);

	platforms.push_back(testplatform);
	_GSD->objects_in_scene.push_back(testplatform->GetPhysics());


	MovingPlatform* test_moving = new MovingPlatform(_RD, Vector2(50, 50), Vector2(50, 400), 4.0f, 2.0f, "platform");
	test_moving->SetPos(Vector2(50, 50));

	test_moving->GetPhysics()->SetCollider(rect);

	platforms.push_back(test_moving);
}
