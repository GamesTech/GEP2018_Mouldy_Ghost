#pragma once

#include "pch.h"
#include "StepTimer.h"
#include "EventHandler.h"

using std::vector;

class Scene
{
public:
	Scene() = default;
	~Scene();

	virtual std::string getType() = 0;

	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine) = 0;

	virtual void Reset() = 0;

	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine);

	virtual void Render
	(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& _commandList);

	//adds the physics from the game's gameobjects to this scene
	void PhysicsInScene(GameStateData* _GSD);

	//Find game objects
	GameObject2D* Find2DGameObjectWithName(std::string name);
	GameObject2D** FindAll2DGameobjectsWithName(std::string name);
	//returns a dynamic array of pointers to GameObject2D, you will need to delete it yourself

	GameObject2D* Find2DGameObjectWithTag(GameObjectTag tag);
	GameObject2D** FindAll2DGameObjectsWithTag(GameObjectTag tag);
	//returns a dynamic array of pointers to GameObject2D, you will need to delete it yourself

	void addListener(EventHandler* _event);
	bool getShouldReset() const { return m_gameShouldReset; }
	void setShouldReset(bool _to) { m_gameShouldReset = _to; }

	void setIdle(float _timer, Event _scene);
	float getIdleTime() const { return m_idle_timer; }
	Event getIdleEvent() const { return m_idle_switch_to; }

protected:
	std::vector<GameObject2D*> sortByZOrder(std::vector<GameObject2D*> objects);

	vector<GameObject3D*> m_3DObjects;
	vector<GameObject2D*> m_2DObjects;
	vector<Sound*> m_sounds;

	vector<EventHandler*> listeners;

	std::unique_ptr<Camera> m_cam = nullptr;
	Vector2 m_cam_pos = Vector2::Zero;
	float m_cam_zoom = 1;
	float m_zoom_rate = 700.0f;
	float m_max_zoom = 1.5f;
	float m_min_zoom = 0.0f;

	RenderData* m_RD;
	GameStateData* m_GSD;
	bool m_gameShouldReset = false;

	float m_idle_timer = 30;
	Event m_idle_switch_to = Event::CHANGE_SCENE_MAIN_MENU;
};