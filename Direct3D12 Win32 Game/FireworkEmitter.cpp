#include "pch.h"
#include "FireworkEmitter.h"
#include <random>


FireworkEmitter::FireworkEmitter(Vector2 _pos, std::string _file, RenderData * _RD) :Emitter( _pos, _file, _RD)
{
}

FireworkEmitter::FireworkEmitter()
{
}


FireworkEmitter::~FireworkEmitter()
{
}

void FireworkEmitter::addParticles(int amount)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> random(0, distributionAngle);
	for (int i = 0; i < amount; i++)
	{
		particles.push_back(Particle(GetPos(), file, RD));
		particles.back().setSprite(allTextures[m_textureIndex].texture.Get());
		Vector2 newPointTo(0, 1);
		newPointTo = rotateVector(newPointTo, angle);
		newPointTo = rotateVector(newPointTo, distributionAngle / -2);
		newPointTo = rotateVector(newPointTo, random(mt));
		//particles.back().setDestination(newPointTo);
		particles.back().setDirection(newPointTo);

		std::random_device rd2;
		std::mt19937 mt2(rd2());
		std::uniform_real_distribution<float> random2(minSpeed, maxSpeed);
		float inputSpeed = random2(mt2);
		particles.back().setSpeed(inputSpeed);

		std::random_device rd3;
		std::mt19937 mt3(rd3());
		std::uniform_real_distribution<float> random3(minLifetime, maxLifetime);
		float inputLifetime = random3(mt3);
		particles.back().setLifetime(inputLifetime);

		Color colorToSet;
		std::random_device rd4;
		std::mt19937 mt4(rd4());
		std::uniform_real_distribution<float> random4(0, 1);
		colorToSet.R(random4(mt4));
		colorToSet.G(random4(mt4));
		colorToSet.B(random4(mt4));
		particles.back().SetColour(colorToSet);
	}
}
