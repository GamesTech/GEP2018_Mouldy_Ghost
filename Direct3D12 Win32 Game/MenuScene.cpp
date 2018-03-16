#include "pch.h"
#include "MenuScene.h"
#include "RenderData.h"
#include "Events.h"


MenuScene::MenuScene()
{
}


MenuScene::~MenuScene()
{
}

void MenuScene::Update(DX::StepTimer const & timer, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	//m_testbutton->Tick(m_GSD);
	m_testMenu->Tick(m_GSD);
}

void MenuScene::Reset()
{

}

void MenuScene::Initialise(RenderData * _RD, GameStateData * _GSD, int _outputWidth, int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	//GEP::This is where I am creating the test objects
	m_cam = new Camera(static_cast<float>(_outputWidth), static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam;
	m_3DObjects.push_back(m_cam);

	//m_testbutton = std::make_unique<MenuButton>(Event::CHANGE_SCENE, _RD, "gens");
	//m_testbutton->SetPos(Vector2(100, 100));
	//m_testbutton->addListener(listeners[0]);

	m_testMenu = std::make_unique<Menu>((m_GSD->window_size / 3.5), MenuButton(Event::CHANGE_SCENE_TEST, _RD, "gens"), "Go to test scene");
	for (int i = 0; i < listeners.size(); i++)
	{
		m_testMenu->addListener(listeners[i]);
	}
	m_testMenu->init();
	m_2DObjects.push_back(m_testMenu.get());
	m_testMenu->addButton(MenuButton(Event::CHANGE_SCENE_PHYSICS, _RD, "gens"), "Go to physics scene");
	m_testMenu->addButton(MenuButton(Event::CHANGE_SCENE_GAME, _RD, "gens"), "Go to game scene");
}
