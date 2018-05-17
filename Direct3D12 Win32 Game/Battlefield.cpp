#include "pch.h"
#include "Battlefield.h"
#include "GameStateData.h"

Battlefield::Battlefield()
{
}

Battlefield::~Battlefield()
{
	platforms.clear();
}

void Battlefield::init(RenderData * _RD, GameStateData * _GSD)
{
	std::unique_ptr<Platform> platform1 = std::make_unique<Platform>(_RD, "platform");
	platform1->SetSpawn(Vector2(430, 400));
	platform1->SetScale(Vector2(2, 1));
	Rectangle rect1 = Rectangle
	(platform1->GetPos().x, platform1->GetPos().y,
		platform1->TextureSize().x * 2,
		platform1->TextureSize().y);
	platform1->GetPhysics()->SetCollider(rect1);
	platforms.push_back(std::move(platform1));

	std::unique_ptr<Platform> platform2 = std::make_unique<Platform>(_RD, "platform");
	platform2->SetSpawn(Vector2(200, 200));
	platform2->SetScale(Vector2(0.5, 0.5));
	Rectangle rect2= Rectangle
	(platform2->GetPos().x, platform2->GetPos().y,
		platform2->TextureSize().x*0.5,
		platform2->TextureSize().y * 0.5);
	platform2->GetPhysics()->SetCollider(rect2);
	platforms.push_back(std::move(platform2));
	
	std::unique_ptr<Platform> platform3 = std::make_unique<Platform>(_RD, "platform");
	platform3->SetSpawn(Vector2(650, 200));
	platform3->SetScale(Vector2(0.5, 0.5));
	Rectangle rect3 = Rectangle
	(platform2->GetPos().x, platform2->GetPos().y,
		platform3->TextureSize().x*0.5,
		platform3->TextureSize().y * 0.5);
	platform3->GetPhysics()->SetCollider(rect2);
	platforms.push_back(std::move(platform3));
	
	std::unique_ptr<Platform> platform4 = std::make_unique<Platform>(_RD, "platform");
	platform4->SetSpawn(Vector2(430, 0));
	platform4->SetScale(Vector2(0.5, 0.5));
	Rectangle rect4 = Rectangle
	(platform2->GetPos().x, platform2->GetPos().y,
		platform4->TextureSize().x*0.5,
		platform4->TextureSize().y * 0.5);
	platform4->GetPhysics()->SetCollider(rect2);
	platforms.push_back(std::move(platform4));


	spawn[0] = Vector2(200, 150);
	spawn[1] = Vector2(650, 150);
	spawn[2] = Vector2(430, -50);
	spawn[3] = Vector2(520, 100);
}

void Battlefield::update(GameStateData * _GSD)
{
}
