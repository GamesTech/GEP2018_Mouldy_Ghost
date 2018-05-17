#pragma once
#include "Stage.h"
class Battlefield : public Stage
{
public:
	Battlefield();
	~Battlefield();

	virtual void init(RenderData* _RD, GameStateData* _GSD) override;
	virtual void update(GameStateData* _GSD) override;
private:

};

