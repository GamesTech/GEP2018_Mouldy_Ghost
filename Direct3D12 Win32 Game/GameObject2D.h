#pragma once
#include "pch.h"
#include "GameObjectTags.h"


//GEP:: Base class for all 2-D objects

using namespace DirectX;
using namespace DirectX::SimpleMath;
struct RenderData;
struct GameStateData;

class ImageGO2D;
class Physics2D;
class EventHandler;

class GameObject2D
{
public:
	GameObject2D();
	virtual ~GameObject2D();

	Vector2 GetPos() { return m_pos; }
	Vector2 GetOrigin() { return m_origin; }
	float GetOri() { return m_orientation; }
	Color GetColour() { return m_colour; }
	Vector2 GetScale() { return m_scale; }

	void SetSpawn(Vector2 _pos);
	void SetPos(Vector2 _pos);
	void ResetPos();
	void SetOrigin(Vector2 _origin) { m_origin = _origin; }
	void SetOri(float _ori);
	void SetColour(Color _col) { m_colour = _col; }
	void SetScale(Vector2 _scale) { m_scale = _scale; }

	virtual void CentreOrigin() = 0;
	
	Physics2D* GetPhysics() { return m_physics; }

	virtual void Tick(GameStateData* _GSD);
	virtual void Render(RenderData* _RD, int _sprite = 0) = 0;

	std::string GetName();
	void SetName(std::string string);

	GameObjectTag GetTag();
	void SetTag(GameObjectTag tag_);

	GameObject2D* GetParent();
	void SetParent(GameObject2D* newParent);
	void AddChild(GameObject2D* object);
	void RemoveChild(GameObject2D* child);


	virtual void CollisionEnter(Physics2D* _collision, Vector2 _normal);
	virtual void Collision(Physics2D* _collision);
	virtual void CollisionExit(Physics2D* _collision);

	void addListener(EventHandler* _event);
protected:
	Vector2 m_spawn_pos = Vector2::Zero;
	Vector2 m_pos = Vector2::Zero;
	Vector2 m_origin = Vector2::Zero;
	float m_orientation = 0.0f;
	Color m_colour = Colors::White;
	Vector2 m_scale = Vector2::One;
	std::string name = "Ordinary game object 2D";
	GameObject2D * parent = nullptr;
	std::vector<GameObject2D*>children;
	GameObjectTag tag = GameObjectTag::UNTAGGED;

	Vector2 previous_pos = Vector2::Zero;
	float previous_ori = 0.0f;

	Physics2D* m_physics;

	std::vector<EventHandler*> listeners;
};

