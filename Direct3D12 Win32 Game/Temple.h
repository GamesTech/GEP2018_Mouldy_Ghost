#pragma once
#include "Stage.h"

class Temple : public Stage
{
public:
	Temple();
	~Temple();


	virtual void init(RenderData* _RD, GameStateData* _GSD) override;
	virtual void update(GameStateData* _GSD) override;

private:

};

