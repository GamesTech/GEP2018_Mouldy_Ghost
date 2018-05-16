#include "pch.h"
#include "Temple.h"
#include "GameStateData.h"

Temple::Temple()
{
	
}

Temple::~Temple()
{
	platforms.clear();
}

void Temple::init(RenderData * _RD, GameStateData * _GSD)
{
	std::unique_ptr<Platform> platform1 = std::make_unique<Platform>(_RD, "platform");

	platform1->SetSpawn(Vector2(600, 400));

	Rectangle rect = Rectangle
	(platform1->GetPos().x, platform1->GetPos().y,
		platform1->TextureSize().x,
		platform1->TextureSize().y);

	platform1->GetPhysics()->SetCollider(rect);

	platforms.push_back(std::move(platform1));

	std::unique_ptr<Platform> platform2 = std::make_unique<Platform>(_RD, "platform");

	platform2->SetSpawn(Vector2(600, 0));

	Rectangle rect1 = Rectangle
	(platform2->GetPos().x, platform2->GetPos().y,
		platform2->TextureSize().x,
		platform2->TextureSize().y);

	platform2->GetPhysics()->SetCollider(rect1);

	platforms.push_back(std::move(platform2));
	

	std::unique_ptr<MovingPlatform> moving1 =
		std::make_unique<MovingPlatform>
		(_RD, Vector2(150,50), Vector2(150,400), 4.0f, 2.0f, "platform");
	moving1->SetSpawn(Vector2(50, 50));
	moving1->SetScale(Vector2(0.5, 0.5));

	Rectangle rect2 = Rectangle
	(platform2->GetPos().x, platform2->GetPos().y,
		platform2->TextureSize().x * 0.5,
		platform2->TextureSize().y * 0.5);

	moving1->GetPhysics()->SetCollider(rect2);

	platforms.push_back(std::move(moving1));

	std::unique_ptr<MovingPlatform> moving2 =
		std::make_unique<MovingPlatform>
		(_RD, Vector2(1050, 400), Vector2(1050, 50), 4.0f, 2.0f, "platform");
	moving2->SetSpawn(Vector2(1050, 400));
	moving2->SetScale(Vector2(0.5, 0.5));

	Rectangle rect3 = Rectangle
	(platform2->GetPos().x, platform2->GetPos().y,
		platform2->TextureSize().x * 0.5,
		platform2->TextureSize().y * 0.5);

	moving2->GetPhysics()->SetCollider(rect3);

	platforms.push_back(std::move(moving2));

	spawn[0] = Vector2(450, -100);
	spawn[1] = Vector2(750, 200);
	spawn[2] = Vector2(450, 200);
	spawn[3] = Vector2(750, -100);
}

void Temple::update(GameStateData * _GSD)
{
}

