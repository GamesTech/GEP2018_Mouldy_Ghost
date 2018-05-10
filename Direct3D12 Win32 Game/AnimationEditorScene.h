#pragma once
#include "Scene.h"
#include "Cursor.h"

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

private:
	std::unique_ptr<Cursor> m_cursor = nullptr;
};

