#pragma once

#include "Scene.h"
#include "Menu.h"

class GameOverScene
	: public Scene
{
public:
	GameOverScene();
	~GameOverScene();

	virtual std::string getType() override { return "GameOver"; };

	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
	virtual void Reset();

	void AddCharacterToScene(Character* _c);
	
	void PlayerEliminated(Character* _c, int index);
	void SortByScores();
private:
	std::vector<Character*> m_chars_in_game;
	Text2D* m_scores[4] = { nullptr, nullptr, nullptr, nullptr };
	std::vector<Character*> m_standings;
	Color m_text_colour[4];
	std::shared_ptr<Menu> m_goBack = nullptr;
};