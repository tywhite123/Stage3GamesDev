#include <nclgl\Window.h>
#include "Renderer.h"
#include <Renderer\Graphics.h>
#include <Physics\Physics.h>
#include <Input\Input.h>

int main() {

	Window w("CSC3224 - Game Engine", 1920, 1080);

	vector<GameObject*> gameObjects;
	gameObjects.push_back(new GameObject(0.0f, 0.0f));

	Graphics graphics(w, gameObjects);
	Physics physics(gameObjects);
	Input input(w, gameObjects);

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float msec = w.GetTimer()->GetTimedMS();
		physics.PhysicsUpdate(msec);
		input.InputUpdate(msec);
		graphics.GraphicsUpdate(msec);
	}



	return 0;
}