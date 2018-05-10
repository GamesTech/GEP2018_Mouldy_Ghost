#pragma once
#include "Scene.h"
#include "Menu.h"

class EditorMenu :
	public Scene
{
public:
	EditorMenu();
	~EditorMenu();
	std::string getType() override { return "EditorMenu"; };
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	void Reset() override;

private:
	Menu m_editorMenu;
};

