#pragma once
#include "Emitter.h"
class FireworkEmitter :
	public Emitter
{
public:
	FireworkEmitter(Vector2 _pos, std::string _file, RenderData* _RD);
	FireworkEmitter();
	~FireworkEmitter();

	virtual void addParticles(int amount) override;
};

