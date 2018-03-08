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
	m_testbutton->Tick(m_GSD);
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

	m_testbutton = std::make_unique<MenuButton>(Event::PLAYER_MOVE, _RD, "gens");
	m_testbutton->SetPos(Vector2(100, 100));
	m_testbutton->addListener(listeners[0]);
	m_2DObjects.push_back(m_testbutton.get());
}
