#pragma once
#include "Scene.h"
#include "MenuButton.h"
#include "Menu.h"


class MenuScene :
	public Scene
{
public:
	MenuScene();
	~MenuScene();

	virtual std::string getType() override { return "MenuScene"; };

	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	virtual void Reset() override;
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
private:
	//std::unique_ptr<MenuButton> m_testbutton = nullptr;
	std::shared_ptr<Menu> m_testMenu = nullptr;
};

