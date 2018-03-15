#pragma once

#include "Scene.h"

using std::vector;

class PhysicsScene : public Scene
{
public:
	PhysicsScene();
	~PhysicsScene();

	virtual std::string getType() override { return "PhysicsScene"; };

	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);

	virtual void Reset();
private:
};