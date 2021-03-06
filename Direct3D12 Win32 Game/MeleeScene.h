#pragma once
#include "Scene.h"
#include "Menu.h"
#include "Particle.h"
#include "Emitter.h"
#include "Characters.h"
#include "TestAnim.h"
class MeleeScene :
	public Scene
{
public:
	MeleeScene();
	~MeleeScene();
	virtual std::string getType() override { return "MeleeScene"; };

	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	virtual void Reset() override;
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
private:
	std::unique_ptr<Menu> m_menu = nullptr;
};