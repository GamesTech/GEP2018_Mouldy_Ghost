#pragma once
#include "GameObject2D.h"
#include "Particle.h"

class Emitter :
	public GameObject2D
{
public:
	Emitter();
	Emitter(Vector2 _pos, std::string _file, RenderData* _RD);
	~Emitter();
	std::vector<Particle> getParticles() { return particles; };
	void setSpeeds(float _min, float _max);
	void setRate(float _rate);
	void setLifetimes(float _min, float _max);
	void setAngle(float _angle);
	void setDistribution(float _angle);
	void addParticles(int amount);
	Vector2 rotateVector(Vector2 _vector, double _angle);

	virtual void CentreOrigin() override;
	virtual void Tick(GameStateData* _GSD) override;
	virtual void Render(RenderData* _RD, int _sprite = 0,
		Vector2 _cam_pos = Vector2::Zero, float _zoom = 1) override;
private:
	float angle;
	float distributionAngle;
	float maxSpeed;
	float minSpeed;
	float spawnRate;
	float maxLifetime;
	float minLifetime;
	bool empty;
	RenderData * RD;
	std::string file;
	std::vector<Particle> particles;
};

