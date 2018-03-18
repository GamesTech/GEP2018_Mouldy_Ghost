#pragma once
#include "Scene.h"

class Menu;
class CharacterManager;

class CharacterSelectScene
	: public Scene
{
public:
	CharacterSelectScene(GameScene* _g_scene);
	~CharacterSelectScene();

	virtual std::string getType() override { return "CharacterScene"; };

	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	virtual void Render
	(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList,
		Vector2 _camera_position = Vector2::Zero);
	virtual void Reset() override;
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
private:
	bool isValid(int i);

	bool m_confirmed[4] = { false, false, false, false };
	short int m_selected_character[4];
	GameScene* m_gameScene;
	CharacterManager* m_ch_manager;
	SimpleMath::Color m_player_tints[4];
};