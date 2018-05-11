#pragma once
#include "ImageGO2D.h"

class Animation2D;

class AnimationContainer :
	public ImageGO2D
{
public:
	AnimationContainer(RenderData* _RD, string _filename);
	AnimationContainer() = default;
	~AnimationContainer() = default;

	void Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom) override;
	void FlipX();
	void switchAnimation(Animation2D* _new);
	void loadAnimations(std::string _file, RenderData* _RD);
	void Tick(GameStateData* _GSD);

	Animation2D* getAnimation() { return active_anim; };
	void changeAnimation(int _direction);

protected:
	bool usesAnimation = false;
	bool flipped = false;

	std::shared_ptr<Animation2D> jump_anim = nullptr;
	std::shared_ptr<Animation2D> idle_anim = nullptr;
	std::shared_ptr<Animation2D> attack_anim = nullptr;
	std::shared_ptr<Animation2D> run_anim = nullptr;
	Animation2D* active_anim = nullptr;
};

