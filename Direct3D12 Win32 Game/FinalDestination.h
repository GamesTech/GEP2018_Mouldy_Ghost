#pragma once
#include "Stage.h"

class FinalDestination : public Stage
{
public:
	FinalDestination();
	~FinalDestination();

	void update(float dt) override;
	void init(RenderData* _RD, GameStateData* _GSD) override;
private:

};

