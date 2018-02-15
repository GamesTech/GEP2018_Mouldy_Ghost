#include "pch.h"
#include "EventScaleUp.h"


EventScaleUp::EventScaleUp()
{
}


EventScaleUp::~EventScaleUp()
{
}

void EventScaleUp::run(ImageGO2D* self)
{
	self->SetScale(self->GetScale() + Vector2(0.5f, 0.5f));
	OutputDebugString(L"Event was called");
}
