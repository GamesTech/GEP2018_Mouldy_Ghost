#pragma once
#include "ImageGO2D.h"

const float m_gravity = 9.8f;

struct BoundingRect
{
	int width;
	int height;
	Vector2 top_left;
	float orientation;
};

enum Axis
{
	X,
	Y,
	BOTH
};

//GEP:: Euler Integration Solve for VERY Basic 2D physics
class Physics2D :
	public ImageGO2D
{
public:
	Physics2D(RenderData* _RD, string _filename);
	~Physics2D();

	void AddForce(Vector2 _push) { m_acc += _push / m_mass; }
	void ResetForce(Axis _axis);

	Vector2 GetVel() { return m_vel; }

	void SetMass(float _mass) { m_mass = _mass; }
	float GetMass() { return m_mass; }
	void SetDrag(float _drag) { m_drag = _drag; }
	float GetDrag() { return m_drag; }
	void SetBounce(float _bounce) { m_bounciness = _bounce; }
	const float GetBounce() { return m_bounciness; }

	virtual void Tick(GameStateData* _GSD);
	
	void SetBoundingRect(BoundingRect _bounding_rect)
	{ m_bounding_rect = _bounding_rect; }

	bool IsColliding(Physics2D* _object, Vector2 &_normal);

	virtual void CollisionEnter(Physics2D* _collision, Vector2 _normal);
	virtual void Collision(Physics2D* _collision);
	virtual void CollisionExit(Physics2D* _collision);

protected:
	bool ContainsPoint(int x, int y);
	const Vector2 GetCollisionNormal
	(Vector2 top_left, Vector2 bottom_right, Vector2 contact);

	BoundingRect m_bounding_rect;
	std::vector<GameObject2D*> currently_colliding;

	Vector2 m_vel;
	Vector2 m_acc;

	float m_mass = 1.0f;
	float m_drag = 0.0f;

	float m_gravity_scale;
	float m_bounciness;
};

