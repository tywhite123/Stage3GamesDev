#pragma once

#include <nclgl\Window.h>
#include <Common\GameObject.h>
#include <Common\MessageQueue.h>

class Input
{
public:
	Input(Window &w, std::vector<GameObject*>& objects, MessageQueue &queue);
	~Input();

	void InputUpdate(float msec);

protected:
	Window* win;
	std::vector<GameObject*>* obj;
	MessageQueue* mQueue;
};

