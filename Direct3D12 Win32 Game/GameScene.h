#pragma once

#include "Scene.h"
#include "Stage.h"
#include "StageManager.h"

#include "CharacterController.h"
#include "CharacterManager.h"
#include "ItemSpawner.h"
#include "Emitter.h"
#include "HUD.h"


enum class GameOverCheck
{
	NONE = -1,
	WAIT,
	FREEZE
};

using std::vector;

class Background;

class GameScene : public Scene
{
public:
	GameScene();
	~ GameScene();

	virtual std::string getType() override { return "GameScene"; }

	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
    
    /*
    Adds a character to the game
    i               - the index of the character controller
    _character      - the name of the character
    _RD             - pointer to the render data
    ai_controlled   - is this character controlled by ai
    demo            - is this the demo scene
    */
	virtual void AddCharacter(int i, std::string _character, bool ai_controlled, bool demo = false);
    //calls remove character on each character in the scene
	void RemoveAllCharacters();
    //find and remove a character from the game scene
	void RemoveCharacter(Character * _char);

	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine);
	virtual void Render
	(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList) override;

	CharacterManager* GetCharacterManager() { return &c_manager; }

	void giveMeItem(RenderData * _RD, GameStateData* _GSD, std::string _name,Vector2 _pos);

	virtual void Reset();
	void LinkSettings();

protected:
	HUD* m_HUD = nullptr;

	Stage* game_stage = nullptr;
	std::unique_ptr<CharacterController> entities[4] = { nullptr, nullptr, nullptr, nullptr };
	std::unique_ptr<Character> players[4] = { nullptr, nullptr, nullptr, nullptr };
	DirectX::SimpleMath::Color player_tints[4];

	std::vector<std::unique_ptr<Background>> m_bg;

	CharacterManager c_manager;
	SpawnHandler* m_spawner;
	ItemSpawner item_spawner;
	StageManager stage_manager;

	bool paused = false;
	std::unique_ptr<Text2D> m_pause_text = nullptr;

	int m_maxLives;
	float m_timeLimit;
	bool m_infiniteLives;
	bool m_infiniteTime;

	float m_timeLeft;

	float m_spawn_item_time = 0;

    //used to delay the switch to a game over scene,
    //on game over the game will wait half a second, then freeze before switching
	GameOverCheck m_game_over_check = GameOverCheck::NONE;
	float m_game_over_timer[2] = { 0,0 };
};