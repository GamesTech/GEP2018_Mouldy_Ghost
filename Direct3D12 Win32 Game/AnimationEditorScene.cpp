#include "pch.h"
#include "AnimationEditorScene.h"
#include "RenderData.h"


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
	m_2DObjects.push_back(m_cursor.get());

	m_back_button = std::make_unique<ClickableButton>(_RD, "button", "Back", Event::CHANGE_SCENE_EDITOR_MENU, Vector2(100, 500), Vector2(.1, .1));
	m_2DObjects.push_back(m_back_button.get());
}

void AnimationEditorScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	Scene::Update(timer, _audEngine);
	if (m_back_button->mouseUpdate(m_cursor.get(), m_GSD))
	{
		for (int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->onNotify(nullptr, *m_back_button->mouseUpdate(m_cursor.get(), m_GSD));
		}
	}
}

void AnimationEditorScene::Reset()
{

}
