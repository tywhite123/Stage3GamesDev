#pragma once

#include <nclgl\Window.h>
#include <Common\GameObject.h>

class Input
{
public:
	Input(Window &w, std::vector<GameObject*>& objects);
	~Input();

	void InputUpdate(float msec);

protected:
	Window* win;
	std::vector<GameObject*>* obj;
};

