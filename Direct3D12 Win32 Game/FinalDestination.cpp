#include "pch.h"

#include "FinalDestination.h"
#include "GameStateData.h"

FinalDestination::FinalDestination()
{
}

FinalDestination::~FinalDestination()
{
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
	std::unique_ptr<Platform> platform = std::make_unique<Platform>(_RD, "grassplatform");

	platform->SetSpawn(Vector2(400, 400));

	platform->SetScale(Vector2(2, 1));
	Rectangle rect = Rectangle
	(platform->GetPos().x, platform->GetPos().y,
		platform->TextureSize().x * 2,
		platform->TextureSize().y );

	

	platform->GetPhysics()->SetCollider(rect);

	platforms.push_back(std::move(platform));
	

	spawn[0] = Vector2(-100, 100);
	spawn[1] = Vector2(150, 100);
	spawn[2] = Vector2(400, 100);
	spawn[3] = Vector2(650, 100);
}
