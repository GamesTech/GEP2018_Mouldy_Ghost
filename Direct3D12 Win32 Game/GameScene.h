#pragma once

#include "Scene.h"
#include "Stage.h"

#include "CharacterController.h"
#include "CharacterManager.h"
#include "ItemSpawner.h"
#include "HUD.h"

using std::vector;

class Background;

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
	void RemoveAllCharacters();
	void RemoveCharacter(Character * _char);

	void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine);
	virtual void Render
	(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList) override;

	CharacterManager* GetCharacterManager() { return &c_manager; }

	void giveMeItem(RenderData * _RD, GameStateData* _GSD, std::string _name,Vector2 _pos);

	virtual void Reset();
	void LinkSettings();

private:
	HUD* m_HUD = nullptr;

	std::unique_ptr<Stage> game_stage = nullptr;
	CharacterController* entities[4] = { nullptr, nullptr, nullptr, nullptr };
	std::unique_ptr<Character> players[4] = { nullptr, nullptr, nullptr, nullptr };
	DirectX::SimpleMath::Color player_tints[4];

	Background* m_bg[3];

	CharacterManager c_manager;
	SpawnHandler* m_spawner;
	ItemSpawner item_spawner;

	int m_maxLives;
	float m_timeLimit;
	bool m_infiniteLives;
	bool m_infiniteTime;

	float m_timeLeft;
};