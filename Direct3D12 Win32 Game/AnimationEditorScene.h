#pragma once
#include "Scene.h"
class AnimationEditorScene :
	public Scene
{
public:
	AnimationEditorScene();
	~AnimationEditorScene();

	std::string getType() override { return "AnimationEditor"; };
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	void Reset() override;
};

