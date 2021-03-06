#pragma once
#include "Scene.h"
#include "MenuButton.h"
#include "Menu.h"

class Background;

class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();

	virtual std::string getType() override { return "MenuScene"; };

	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	virtual void Reset() override;
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
private:
	std::shared_ptr<Menu> m_testMenu = nullptr;
	std::unique_ptr<Background> m_background = nullptr;
};