#pragma once

#include "Scene.h"
#include "pch.h"

using std::vector;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	virtual void Initialise(RenderData * _RD, GameStateData* _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);

	virtual void Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
	virtual void Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList);

private:
};