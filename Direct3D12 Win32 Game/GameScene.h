#pragma once

#include "Scene.h"
#include "Stage.h"

using std::vector;

class GameScene : public Scene
{
public:
	GameScene();
	~ GameScene();

	virtual std::string getType() override { return "GameScene"; };

	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);

	void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine);

	virtual void Reset();

private:
	std::unique_ptr<Stage> game_stage = nullptr;
};