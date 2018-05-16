#include "pch.h"
#include "AnimationEditorScene.h"
#include "RenderData.h"
#include "AnimationEditorHandler.h"
#include "AnimationContainer.h"
#include "Animation2D.h"


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

	m_back_button = std::make_unique<ClickableButton>(_RD, "button", "Back", Event::CHANGE_SCENE_EDITOR_MENU, Vector2(700, 550), Vector2(.05, .05));
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
		m_characters.push_back(std::make_unique<AnimationContainer>(_RD, "Error"));
		m_characters.back()->SetPos(Vector2(500, 100));
		m_characters.back()->loadAnimations(m_character_manager.GetCharacter(i).GetName(), _RD);
		m_editor_handler->addAnimationContainer(m_characters.back().get());
	}

	//Character select
	m_prev_character = std::make_unique<ClickableButton>(_RD, "button", "<Character", Event::ANIMATION_EDITOR_PREV_CHARACTER, Vector2(100, 50), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_prev_character.get());
	m_next_character = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_NEXT_CHARACTER, Vector2(220, 50), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_next_character.get());
	m_character_text = std::make_unique<Text2D>("Unassigned");
	m_character_text->SetPos(Vector2(270, 25));
	m_2DObjects.push_back(m_character_text.get());
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
	m_framerate_text = std::make_unique<Text2D>("Unassigned");
	m_framerate_text->SetPos(Vector2(270, 145));
	m_2DObjects.push_back(m_framerate_text.get());
	//Number of Frames
	m_decrease_frames = std::make_unique<ClickableButton>(_RD, "button", "<Frames", Event::ANIMATION_EDITOR_DECREASE_FRAMES, Vector2(100, 230), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_frames.get());
	m_increase_frames = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_FRAMES, Vector2(220, 230), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_frames.get());
	m_frames_text = std::make_unique<Text2D>("Unassigned");
	m_frames_text->SetPos(Vector2(270, 205));
	m_2DObjects.push_back(m_frames_text.get());
	//x Increments
	m_decrease_x_increments = std::make_unique<ClickableButton>(_RD, "button", "<X Increments", Event::ANIMATION_EDITOR_DECREASE_X_INCREMENTS, Vector2(100, 290), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_x_increments.get());
	m_increase_x_increments = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_X_INCREMENTS, Vector2(220, 290), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_x_increments.get());
	m_x_increments_text = std::make_unique<Text2D>("Unassigned");
	m_x_increments_text->SetPos(Vector2(270, 265));
	m_2DObjects.push_back(m_x_increments_text.get());
	//Y Increments
	m_decrease_y_increments = std::make_unique<ClickableButton>(_RD, "button", "<Y Increments", Event::ANIMATION_EDITOR_DECREASE_Y_INCREMENTS, Vector2(100, 350), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_y_increments.get());
	m_increase_y_increments = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_Y_INCREMENTS, Vector2(220, 350), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_y_increments.get());
	m_y_increments_text = std::make_unique<Text2D>("Unassigned");
	m_y_increments_text->SetPos(Vector2(270, 325));
	m_2DObjects.push_back(m_y_increments_text.get());
	//Box Width
	m_decrease_box_width = std::make_unique<ClickableButton>(_RD, "button", "<Box Width", Event::ANIMATION_EDITOR_DECREASE_BOX_WIDTH, Vector2(100, 410), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_box_width.get());
	m_increase_box_width = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_BOX_WIDTH, Vector2(220, 410), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_box_width.get());
	m_box_width_text = std::make_unique<Text2D>("Unassigned");
	m_box_width_text->SetPos(Vector2(270, 385));
	m_2DObjects.push_back(m_box_width_text.get());
	//Box Height
	m_decrease_box_height = std::make_unique<ClickableButton>(_RD, "button", "<Box Height", Event::ANIMATION_EDITOR_DECREASE_BOX_HEIGHT, Vector2(100, 470), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_box_height.get());
	m_increase_box_height = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_BOX_HEIGHT, Vector2(220, 470), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_box_height.get());
	m_box_height_text = std::make_unique<Text2D>("Unassigned");
	m_box_height_text->SetPos(Vector2(270, 445));
	m_2DObjects.push_back(m_box_height_text.get());
	//Furthest left position
	m_decrease_furthest_left = std::make_unique<ClickableButton>(_RD, "button", "<Furthest Left", Event::ANIMATION_EDITOR_DECREASE_FURTHEST_LEFT, Vector2(100, 530), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_furthest_left.get());
	m_increase_furthest_left = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_FURTHEST_LEFT, Vector2(220, 530), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_furthest_left.get());
	m_furthest_left_text = std::make_unique<Text2D>("Unassigned");
	m_furthest_left_text->SetPos(Vector2(270, 505));
	m_2DObjects.push_back(m_furthest_left_text.get());
	//Start x
	m_decrease_start_x = std::make_unique<ClickableButton>(_RD, "button", "<Start X", Event::ANIMATION_EDITOR_DECREASE_START_X, Vector2(500, 230), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_start_x.get());
	m_increase_start_x = std::make_unique<ClickableButton>(_RD, "button", ">", Event::ANIMATION_EDITOR_INCREASE_START_X, Vector2(620, 230), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_start_x.get());
	m_start_x_text = std::make_unique<Text2D>("Unassigned");
	m_start_x_text->SetPos(Vector2(670, 205));
	m_2DObjects.push_back(m_start_x_text.get());
	//Start y
	m_decrease_start_y = std::make_unique<ClickableButton>(_RD, "button", "<Start Y", Event::ANIMATION_EDITOR_DECREASE_START_Y, Vector2(500, 290), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_decrease_start_y.get());
	m_increase_start_y = std::make_unique<ClickableButton>(_RD, "button", "<", Event::ANIMATION_EDITOR_INCREASE_START_Y, Vector2(620, 290), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_increase_start_y.get());
	m_start_y_text = std::make_unique<Text2D>("Unassigned");
	m_start_y_text->SetPos(Vector2(670, 265));
	m_2DObjects.push_back(m_start_y_text.get());
	//Save
	m_save_character = std::make_unique<ClickableButton>(_RD, "button", "Save Character", Event::ANIMATION_EDITOR_SAVE_DATA, Vector2(480, 550), Vector2(0.05, 0.05));
	m_2DObjects.push_back(m_save_character.get());
}

void AnimationEditorScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	Scene::Update(timer, _audEngine);

	//get values for animation and set text
	Animation2D* temp = m_characters[m_editor_handler->getSelectedCharIndex()]->getAnimation();
	int temp_num = 0;
	m_character_text->SetText(m_editor_handler->getSelectedChar().GetName());
	temp_num = temp->getFramerate();
	m_framerate_text->SetText(std::to_string(temp_num));
	temp_num = temp->getMaxFrames();
	m_frames_text->SetText(std::to_string(temp_num));
	temp_num = temp->getIncrements().x;
	m_x_increments_text->SetText(std::to_string(temp_num));
	temp_num = temp->getIncrements().y;
	m_y_increments_text->SetText(std::to_string(temp_num));
	temp_num = temp->getSpriteBox().width;
	m_box_width_text->SetText(std::to_string(temp_num));
	temp_num = temp->getSpriteBox().height;
	m_box_height_text->SetText(std::to_string(temp_num));
	temp_num = temp->getFurthestLeftPos();
	m_furthest_left_text->SetText(std::to_string(temp_num));
	temp_num = temp->getSpriteboxStartPos().x;
	m_start_x_text->SetText(std::to_string(temp_num));
	temp_num = temp->getSpriteboxStartPos().y;
	m_start_y_text->SetText(std::to_string(temp_num));


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
	if (m_decrease_frames->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_decrease_frames->getEvent());
		}
	}
	if (m_increase_frames->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_increase_frames->getEvent());
		}
	}
	if (m_decrease_x_increments->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_decrease_x_increments->getEvent());
		}
	}
	if (m_increase_x_increments->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_increase_x_increments->getEvent());
		}
	}
	if (m_decrease_y_increments->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_decrease_y_increments->getEvent());
		}
	}
	if (m_increase_y_increments->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_increase_y_increments->getEvent());
		}
	}
	if (m_decrease_box_width->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_decrease_box_width->getEvent());
		}
	}
	if (m_increase_box_width->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_increase_box_width->getEvent());
		}
	}
	if (m_decrease_box_height->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_decrease_box_height->getEvent());
		}
	}
	if (m_increase_box_height->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_increase_box_height->getEvent());
		}
	}
	if (m_decrease_furthest_left->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_decrease_furthest_left->getEvent());
		}
	}
	if (m_increase_furthest_left->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_increase_furthest_left->getEvent());
		}
	}
	if (m_decrease_start_x->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_decrease_start_x->getEvent());
		}
	}
	if (m_increase_start_x->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_increase_start_x->getEvent());
		}
	}
	if (m_decrease_start_y->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_decrease_start_y->getEvent());
		}
	}
	if (m_increase_start_y->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_increase_start_y->getEvent());
		}
	}
	if (m_save_character->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, m_save_character->getEvent());
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
