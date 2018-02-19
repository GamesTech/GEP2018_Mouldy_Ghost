#pragma once
#include "Physics2D.h"

class Platform : public ImageGO2D
{
public:
	//using Physics2D::Physics2D;
	Platform(RenderData* _RD, string _filename);;
	~Platform();

private:
};

