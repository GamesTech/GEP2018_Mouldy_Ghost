#pragma once

#include "StepTimer.h"
using std::vector;

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine) = 0;

	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine) = 0;

	virtual void Render
	(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList) = 0;

protected:
	vector<GameObject3D*> m_3DObjects;
	vector<GameObject2D*> m_2DObjects;
	vector<Sound*> m_sounds;

	Camera* m_cam;

	RenderData* m_RD;
	GameStateData* m_GSD;
};