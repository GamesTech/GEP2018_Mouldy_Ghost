#include "pch.h"
#include "AnimationEditorScene.h"
#include "RenderData.h"
#include "AnimationEditorHandler.h"
#include "AnimationContainer.h"


AnimationEditorScene::AnimationEditorScene()
{
}


AnimationEditorScene::~AnimationEditorScene()
{
}

void AnimationEditorScene::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	//GEP::This is where I am creating the test objects
	m_cam = std::make_unique<Camera>(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam.get();
	m_3DObjects.push_back(m_cam.get());

	m_cursor = std::make_unique<Cursor>(_RD, "cursor");
	m_cursor->setZ(-1);
	m_2DObjects.push_back(m_cursor.get());

	m_back_button = std::make_unique<ClickableButton>(_RD, "button", "Back", Event::CHANGE_SCENE_EDITOR_MENU, Vector2(600, 550), Vector2(.05, .05));
	m_2DObjects.push_back(m_back_button.get());


	for (int i = 0; i < listeners.size(); i++)
	{
		if (listeners[i]->getType() == "AnimationEditor")
		{
			m_editor_handler = static_cast<AnimationEditorHandler*>(listeners[i]);
		}
	}

	m_character_manager.PopulateCharacterList(_RD);

	m_editor_handler->tieCharacterManager(&m_character_manager);

	for (int i = 0; i < m_character_manager.GetCharCount(); i++)
	{
		m_characters.push_back(std::make_unique<AnimationContainer>(_RD, m_character_manager.GetCharacter(i).GetName() + "Walk"));
		m_characters.back()->SetPos(Vector2(500, 100));
		m_characters.back()->loadAnimations(m_character_manager.GetCharacter(i).GetName(), _RD);
		m_editor_handler->addAnimationContainer(m_characters.back().get());
	}

	//Character select
	m_prev_character = std::make_unique<ClickableButton>(_RD, "button", "<Character", Event::ANIMATION_EDITOR_PREV_CHARACTER, Vector2(100, 50), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_prev_character.get());
	m_next_character = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_NEXT_CHARACTER, Vector2(220, 50), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_next_character.get());
	//Animation
	m_prev_animation = std::make_unique<ClickableButton>(_RD, "button", "<Animation", Event::ANIMATION_EDITOR_PREV_ANIM, Vector2(100, 110), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_prev_animation.get());
	m_next_animation = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_NEXT_ANIM, Vector2(220, 110), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_next_animation.get());
	//Framerate
	m_decrease_framerate = std::make_unique<ClickableButton>(_RD, "button", "<Framerate", Event::ANIMATION_EDITOR_DECREASE_FRAMERATE, Vector2(100, 170), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_framerate.get());
	m_increase_framerate = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_FRAMERATE, Vector2(220, 170), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_framerate.get());
	//Number of Frames
	m_decrease_frames = std::make_unique<ClickableButton>(_RD, "button", "<Frames", Event::ANIMATION_EDITOR_DECREASE_FRAMES, Vector2(100, 230), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_frames.get());
	m_increase_frames = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_FRAMES, Vector2(220, 230), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_frames.get());
	//x Increments
	m_decrease_x_increments = std::make_unique<ClickableButton>(_RD, "button", "<X Increments", Event::ANIMATION_EDITOR_DECREASE_X_INCREMENTS, Vector2(100, 290), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_x_increments.get());
	m_increase_x_increments = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_X_INCREMENTS, Vector2(220, 290), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_x_increments.get());
	//Y Increments
	m_decrease_y_increments = std::make_unique<ClickableButton>(_RD, "button", "<Y Increments", Event::ANIMATION_EDITOR_DECREASE_Y_INCREMENTS, Vector2(100, 350), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_y_increments.get());
	m_increase_y_increments = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_Y_INCREMENTS, Vector2(220, 350), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_y_increments.get());
	//Box Width
	m_decrease_box_width = std::make_unique<ClickableButton>(_RD, "button", "<Box Width", Event::ANIMATION_EDITOR_DECREASE_BOX_WIDTH, Vector2(100, 410), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_box_width.get());
	m_increase_box_width = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_BOX_WIDTH, Vector2(220, 410), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_box_width.get());
	//Box Height
	m_decrease_box_height = std::make_unique<ClickableButton>(_RD, "button", "<Box Height", Event::ANIMATION_EDITOR_DECREASE_BOX_HEIGHT, Vector2(100, 470), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_box_height.get());
	m_increase_box_height = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_BOX_HEIGHT, Vector2(220, 470), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_box_height.get());
	//Furthest left position
	m_decrease_furthest_left = std::make_unique<ClickableButton>(_RD, "button", "<Furthest Left", Event::ANIMATION_EDITOR_DECREASE_FURTHEST_LEFT, Vector2(100, 530), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_furthest_left.get());
	m_increase_furthest_left = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_FURTHEST_LEFT, Vector2(220, 530), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_furthest_left.get());
	//Start x
	m_decrease_start_x = std::make_unique<ClickableButton>(_RD, "button", "<Start X", Event::ANIMATION_EDITOR_DECREASE_START_X, Vector2(500, 230), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_start_x.get());
	m_increase_start_x = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_START_X, Vector2(620, 230), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_start_x.get());
	//Start y
	m_decrease_start_y = std::make_unique<ClickableButton>(_RD, "button", "<Start Y", Event::ANIMATION_EDITOR_DECREASE_START_Y, Vector2(500, 290), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_start_y.get());
	m_increase_start_y = std::make_unique<ClickableButton>(_RD, "button", "<", Event::ANIMATION_EDITOR_INCREASE_START_Y, Vector2(620, 290), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_start_y.get());
	//Save
}

void AnimationEditorScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	Scene::Update(timer, _audEngine);
	if (m_back_button->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_back_button->getEvent());
		}
	}
	if (m_prev_character->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_prev_character->getEvent());
		}
	}
	if (m_next_character->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_next_character->getEvent());
		}
	}
	if (m_prev_animation->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_prev_animation->getEvent());
		}
	}
	if (m_next_animation->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_next_animation->getEvent());
		}
	}
	if (m_decrease_framerate->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_decrease_framerate->getEvent());
		}
	}
	if (m_increase_framerate->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_increase_framerate->getEvent());
		}
	}

	m_characters[m_editor_handler->getSelectedCharIndex()]->Tick(m_GSD);
}

void AnimationEditorScene::Render(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList)
{
	Scene::Render(_commandList);

	//primative batch
	m_RD->m_effect->SetProjection(m_cam->GetProj());
	m_RD->m_effect->SetView(m_cam->GetView());
	m_RD->m_effect->Apply(_commandList.Get());
	m_RD->m_effect->EnableDefaultLighting();
	ID3D12DescriptorHeap* heaps[] = { m_RD->m_resourceDescriptors->Heap() };
	_commandList->SetDescriptorHeaps(_countof(heaps), heaps);
	m_RD->m_spriteBatch->Begin(_commandList.Get());

/*
	m_character->SetPos(Vector2(500, 100));
	m_character->Render(m_RD);*/
	m_characters[m_editor_handler->getSelectedCharIndex()]->Render(m_RD, 0, m_cam_pos, m_cam_zoom);
	m_RD->m_spriteBatch->End();
}

void AnimationEditorScene::Reset()
{

}
