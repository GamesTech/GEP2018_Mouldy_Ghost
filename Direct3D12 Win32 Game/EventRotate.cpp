#include "pch.h"
#include "EventRotate.h"


EventRotate::EventRotate()
{
}


EventRotate::~EventRotate()
{
}

void EventRotate::run(ImageGO2D * self)
{
	self->SetOri(self->GetOri() + 0.01f);
}
