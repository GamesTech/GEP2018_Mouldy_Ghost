#pragma once

#include "Scene.h"
#include "Menu.h"

struct FallingCharacter
{
	Character* character = nullptr;
	int target;
};

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
	
    //eliminated players go to the bottom of the standings
	void PlayerEliminated(Character* _c);
    //sort non-eliminated players by their scores
	void SortByScores();
private:
	std::vector<Character*> m_chars_in_game;
	Text2D* m_scores[4] = { nullptr, nullptr, nullptr, nullptr };
	std::vector<FallingCharacter> m_falling;
	ImageGO2D m_podiums[3];
	Vector2 m_podium_positions[4];
	std::vector<Character*> m_standings;
};