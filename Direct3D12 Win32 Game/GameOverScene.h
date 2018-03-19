#pragma once

#include "Scene.h"

class GameOverScene
	: public Scene
{
	GameOverScene();
	~GameOverScene();

	virtual std::string getType() override { return "GameOver"; };

	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	virtual void Reset() override;
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);

	void ShowStandings();

	void PlayerEliminated(Character* _character);
	void SortByScores(Character** _character);
private:
	Text2D* m_scores[4] = { nullptr, nullptr, nullptr, nullptr };
	std::vector<Character*> m_standings;
	Color m_text_colour[4];
};