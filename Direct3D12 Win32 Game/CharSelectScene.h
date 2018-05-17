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
	(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList);
	virtual void Reset() override;
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
private:
	void addAI();
	void removeAI();
	void removeAI(int i);

	bool isValid(int i);
	std::string ai_to_add[4] = { "", "", "", "" };
	bool m_confirmed[4] = { false, false, false, false };
	short int m_selected_character[4];
	GameScene* m_gameScene;
	CharacterManager* m_ch_manager;
	SimpleMath::Color m_player_tints[4];
	Text2D* m_instructions[2];
};