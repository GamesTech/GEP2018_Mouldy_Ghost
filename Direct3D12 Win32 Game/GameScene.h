#pragma once

#include "Scene.h"

using std::vector;

class GameScene : public Scene
{
public:
	GameScene();
	~ GameScene();

	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);

	virtual void Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
	virtual void Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList);

private:
};