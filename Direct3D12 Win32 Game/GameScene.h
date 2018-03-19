#pragma once

#include "Scene.h"
#include "Stage.h"

#include "CharacterController.h"
#include "CharacterManager.h"
#include "ItemSpawner.h"
#include "HUD.h"

using std::vector;

class GameScene : public Scene
{
public:
	GameScene();
	~ GameScene();

	virtual std::string getType() override { return "GameScene"; };

	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
	void AddCharacter(int i, std::string _character, RenderData* _RD);
	void RemoveCharacter(Character * _char);

	void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine);
	virtual void Render
	(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList,
		Vector2 _camera_position = Vector2::Zero) override;

	CharacterManager* GetCharacterManager() { return &c_manager; }

	void giveMeItem(RenderData * _RD, GameStateData* _GSD, std::string _name);

	virtual void Reset();

private:
	HUD* m_HUD = nullptr;

	std::unique_ptr<Stage> game_stage = nullptr;
	CharacterController* entities[4] = { nullptr, nullptr, nullptr, nullptr };
	Character* players[4] = { nullptr, nullptr, nullptr, nullptr };
	DirectX::SimpleMath::Color player_tints[4];

	CharacterManager c_manager;
	std::unique_ptr<SpawnHandler> m_spawner;
	ItemSpawner item_spawner;
};