#include "pch.h"
#include "Temple.h"
#include "GameStateData.h"

Temple::Temple()
{
	
}

Temple::~Temple()
{
	for (auto& platform : platforms)
	{
		delete platform;
		platform = nullptr;
	}

	platforms.clear();
}

void Temple::init(RenderData * _RD, GameStateData * _GSD)
{
	Platform* testplatform = new Platform(_RD, "platform");

	testplatform->SetSpawn(Vector2(600, 400));

	Rectangle rect = Rectangle
	(testplatform->GetPos().x, testplatform->GetPos().y,
		testplatform->TextureSize().x,
		testplatform->TextureSize().y);

	testplatform->GetPhysics()->SetCollider(rect);

	platforms.push_back(testplatform);


	Platform* platform = new Platform(_RD, "platform");

	platform->SetSpawn(Vector2(600, 0));

	Rectangle rect1 = Rectangle
	(platform->GetPos().x, platform->GetPos().y,
		platform->TextureSize().x,
		platform->TextureSize().y);

	platform->GetPhysics()->SetCollider(rect1);

	platforms.push_back(platform);
	


	MovingPlatform* test_moving = new MovingPlatform(_RD, Vector2(150, 50), Vector2(150, 400), 4.0f, 2.0f, "platform");
	test_moving->SetPos(Vector2(50, 50));
	test_moving->SetScale(Vector2(0.5, 0.5));

	Rectangle rect2 = Rectangle
	(platform->GetPos().x, platform->GetPos().y,
		platform->TextureSize().x * 0.5,
		platform->TextureSize().y * 0.5);

	test_moving->GetPhysics()->SetCollider(rect2);

	platforms.push_back(test_moving);

	MovingPlatform* moving = new MovingPlatform(_RD, Vector2(1050, 400), Vector2(1050, 50), 4.0f, 2.0f, "platform");
	moving->SetPos(Vector2(1050, 400));
	moving->SetScale(Vector2(0.5, 0.5));

	Rectangle rect3 = Rectangle
	(platform->GetPos().x, platform->GetPos().y,
		platform->TextureSize().x * 0.5,
		platform->TextureSize().y * 0.5);

	moving->GetPhysics()->SetCollider(rect3);

	platforms.push_back(moving);

	spawn[0] = Vector2(450, -100);
	spawn[1] = Vector2(750, 200);
	spawn[2] = Vector2(450, 200);
	spawn[3] = Vector2(750, -100);
}

void Temple::update(GameStateData * _GSD)
{
}

