#pragma once

#include "Scene.h"
#include "Stage.h"

#include "CharacterController.h"
#include "CharacterManager.h"
#include "ItemSpawner.h"

using std::vector;

class GameScene : public Scene
{
public:
	GameScene();
	~ GameScene();

	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);

	void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine);

	virtual void Reset();

private:
	std::unique_ptr<Stage> game_stage = nullptr;
	CharacterController* entities[4] = { nullptr, nullptr, nullptr, nullptr };
	Character* players[4] = { nullptr, nullptr, nullptr, nullptr };

	CharacterManager c_manager;
	ItemSpawner item_spawner;
};