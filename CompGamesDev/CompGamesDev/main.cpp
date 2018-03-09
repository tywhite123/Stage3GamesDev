#include <nclgl\Window.h>
#include "Renderer.h"
#include <Common\EventQueue.h>
#include <Renderer\Graphics.h>
#include <Physics\Physics.h>
#include <Input\Input.h>

int main() {

	Window w("CSC3224 - Game Engine", 1920, 1080);

	vector<GameObject*> gameObjects;
	gameObjects.push_back(new GameObject(0.0f, 0.0f));

	EventQueue* queue = new EventQueue();

	Graphics graphics(w, gameObjects, queue);
	Physics physics(gameObjects, queue);
	Input input(w, gameObjects, queue);

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float msec = w.GetTimer()->GetTimedMS();
		input.InputUpdate(msec);
		physics.PhysicsUpdate(msec);
		
		graphics.GraphicsUpdate(msec);
	}



	return 0;
}