#pragma once
#include "Scene.h"
#include "Cursor.h"
#include "ClickableButton.h"
#include "CharacterManager.h"

class AnimationEditorHandler;
class AnimationContainer;

class AnimationEditorScene :
	public Scene
{
public:
	AnimationEditorScene();
	~AnimationEditorScene();

	std::string getType() override { return "AnimationEditor"; };
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	void Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList) override;
	void Reset() override;

private:
	std::unique_ptr<Cursor> m_cursor = nullptr;
	std::unique_ptr<ClickableButton> m_back_button = nullptr;
	std::unique_ptr<ClickableButton> m_next_character = nullptr;
	std::unique_ptr<ClickableButton> m_prev_character = nullptr;
	std::unique_ptr<ClickableButton> m_next_animation = nullptr;
	std::unique_ptr<ClickableButton> m_prev_animation = nullptr;
	std::unique_ptr<ClickableButton> m_decrease_framerate = nullptr;
	std::unique_ptr<ClickableButton> m_increase_framerate = nullptr;
	std::unique_ptr<ClickableButton> m_decrease_frames = nullptr;
	std::unique_ptr<ClickableButton> m_increase_frames = nullptr;
	std::unique_ptr<ClickableButton> m_decrease_x_increments = nullptr;
	std::unique_ptr<ClickableButton> m_increase_x_increments = nullptr;
	std::unique_ptr<ClickableButton> m_decrease_y_increments = nullptr;
	std::unique_ptr<ClickableButton> m_increase_y_increments = nullptr;
	std::unique_ptr<ClickableButton> m_decrease_box_width = nullptr;
	std::unique_ptr<ClickableButton> m_increase_box_width = nullptr;
	std::unique_ptr<ClickableButton> m_decrease_box_height = nullptr;
	std::unique_ptr<ClickableButton> m_increase_box_height = nullptr;
	std::unique_ptr<ClickableButton> m_decrease_furthest_left = nullptr;
	std::unique_ptr<ClickableButton> m_increase_furthest_left = nullptr;
	std::unique_ptr<ClickableButton> m_decrease_start_x = nullptr;
	std::unique_ptr<ClickableButton> m_increase_start_x = nullptr;
	std::unique_ptr<ClickableButton> m_decrease_start_y = nullptr;
	std::unique_ptr<ClickableButton> m_increase_start_y = nullptr;
	std::unique_ptr<ClickableButton> m_save_character = nullptr;
	std::vector<std::unique_ptr<AnimationContainer>> m_characters;
	CharacterManager m_character_manager;
	AnimationEditorHandler* m_editor_handler;
};

