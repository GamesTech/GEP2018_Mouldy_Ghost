#include "pch.h"

#include "FinalDestination.h"
#include "GameStateData.h"

FinalDestination::FinalDestination()
{
}

FinalDestination::~FinalDestination()
{
}

void FinalDestination::update(float dt)
{
}

void FinalDestination::init(RenderData* _RD, GameStateData * _GSD)
{
	Platform* testplatform = new Platform(_RD, "twist");

	testplatform->SetPos(Vector2(200, 400));
	//testplatform->SetScale(Vector2(2, 0.2));
	//testplatform->CentreOrigin();

	Rectangle rect = Rectangle
	(testplatform->GetPos().x, testplatform->GetPos().y,
		testplatform->TextureSize().x,
		testplatform->TextureSize().y);
	
	/*testplatform->CentreOrigin();*/

	testplatform->GetPhysics()->SetCollider(rect);

	platforms.push_back(testplatform);
	_GSD->objects_in_scene.push_back(testplatform->GetPhysics());

}
