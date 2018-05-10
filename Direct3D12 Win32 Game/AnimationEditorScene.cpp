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

	m_cursor = std::make_unique<Cursor>(_RD, "gens");
	m_2DObjects.push_back(m_cursor.get());
}

void AnimationEditorScene::Reset()
{

}
