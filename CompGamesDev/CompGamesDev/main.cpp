#include <nclgl\Window.h>
#include "Renderer.h"
#include <Renderer\Graphics.h>
#include <Physics\Physics.h>
#include <Input\Input.h>

/*int main() {
	Window w("Test", 800, 600);


}*/

int main() {
	/*Window w("Index Buffers!", 800, 600, false);
	if (!w.HasInitialised()) {
		return -1;
	}

	Renderer renderer(w);
	if (!renderer.HasInitialised()) {
		return -1;
	}

	Graphics graphics(w, renderer);

	w.LockMouseToWindow(true);
	w.ShowOSPointer(false);

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		renderer.UpdateScene(w.GetTimer()->GetTimedMS());
		renderer.RenderScene();
	}*/

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