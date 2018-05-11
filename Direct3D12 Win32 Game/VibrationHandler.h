#pragma once
#include "EventHandler.h"
#include "StepTimer.h"

class VibrationHandler
	: public EventHandler
{
public:
	VibrationHandler() = default;
	~VibrationHandler() = default;

	void onNotify(GameObject2D* entity_, Event event_);
	std::string getType() { return "Vibration"; }

	void addGamePad(DirectX::GamePad* _gp) { m_game_pads = _gp; }

	void Tick(DX::StepTimer const & timer);
private:
	void setVibration(int player, float l, float r, float time, float rt = 0, float lt = 0);
	DirectX::GamePad* m_game_pads;
	float m_vibration_timer[4] = { 4, 0 };
};