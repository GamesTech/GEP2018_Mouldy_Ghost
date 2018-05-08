#pragma once
#include "GameScene.h"

class DemoScene
	: public GameScene
{
public:
	DemoScene() = default;
	~DemoScene() = default;

	std::string getType() override { return "DemoScene"; }
	void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
};