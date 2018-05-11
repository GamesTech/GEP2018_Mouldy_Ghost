#pragma once
#include "Scene.h"
#include "Menu.h"

class StageSelectScene : public Scene
{
public:
	StageSelectScene();
	~StageSelectScene();

	virtual std::string getType() override { return "StageSelect"; };

	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	virtual void Reset() override;
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);

private:
	std::unique_ptr<Menu> m_StageSelectMenu = nullptr;
};

