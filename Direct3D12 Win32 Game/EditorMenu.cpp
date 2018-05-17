#include "pch.h"
#include "EditorMenu.h"
#include "RenderData.h"


EditorMenu::EditorMenu()
{
}


EditorMenu::~EditorMenu()
{
}

void EditorMenu::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	//GEP::This is where I am creating the test objects
	m_cam = std::make_unique<Camera>(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam.get();
	m_3DObjects.push_back(m_cam.get());

	m_editorMenu = Menu(Vector2(100, _GSD->window_size.y / 10), MenuButton(Event::CHANGE_SCENE_ANIMATION_EDITOR, _RD, "gens"), "Animation Editor");


	for (int i = 0; i < listeners.size(); i++)
	{
		m_editorMenu.addListener(listeners[i]);
	}
	m_editorMenu.init();

	m_2DObjects.push_back(&m_editorMenu);

	m_editorMenu.addButton(MenuButton(Event::CHANGE_SCENE_MELEE_MENU, _RD, "gens"), "Back");
}

void EditorMenu::Reset()
{

}
