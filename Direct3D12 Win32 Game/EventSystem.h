#pragma once
class EventSystem
{
public:
	EventSystem();
	~EventSystem();
	virtual void run() {};
	virtual void run(ImageGO2D* self) {};
};

