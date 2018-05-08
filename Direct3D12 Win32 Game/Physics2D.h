#pragma once

class Item;

enum Axis
{
	X_AXIS,
	Y_AXIS,
	BOTH_AXES
};

//GEP:: Euler Integration Solve for VERY Basic 2D physics
class Physics2D
{
public:
	Physics2D();
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
	void SetGrav(float _grav) { m_gravity_scale = _grav; }
	const float GetGrav() { return m_gravity_scale; }
	void SetOwner(GameObject2D* _owner) { m_owner = _owner; }
	GameObject2D* GetOwner() { return m_owner; }

	virtual void Tick(GameStateData* _GSD, Vector2& _pos);
	
	void SetCollider(Rectangle _collider){ m_collider = _collider; }
	Rectangle GetCollider() { if (&m_collider) { return m_collider; } else return Rectangle(); }
	void MoveCollider(Vector2 _pos) {m_collider.Offset(_pos.x, _pos.y);}

	void ScaleCollider(Vector2 _by, Vector2 _owner_scale);

	void removeFromCurrentlyColliding(Physics2D* col);

	Item* GetItem();
#if _DEBUG
	void RenderCorners(Vector2 _cam);
#endif;

protected:
	GameObject2D* m_owner = nullptr;

	Rectangle m_collider;
	std::vector<Physics2D*> currently_colliding;

	void CheckForCollisions(GameStateData * _GSD, Vector2& _pos);
	Vector2 GetNormal(Vector2 _point);

	Vector2 m_vel;
	Vector2 m_acc;

	float m_mass = 1.0f;
	float m_drag = 0.0f;

	float m_gravity_scale;
	float m_bounciness;

	Vector2 m_collider_scale = Vector2::One;
};