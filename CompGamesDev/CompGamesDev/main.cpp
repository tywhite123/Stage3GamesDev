#include <nclgl\Window.h>
#include "Renderer.h"
#include <Common\EventQueue.h>
#include <Renderer\Graphics.h>
#include <Physics\Physics.h>
#include <Input\Input.h>
#include <Audio\Audio.h>
#include <FileIO\GameLoader.h>


int main() {

	Window w("CSC3224 - Game Engine", 1920, 1080);

	vector<GameObject*> gameObjects;

	GameLoader("..\\TestLevel\\test.csv", gameObjects);


	EventQueue* queue = new EventQueue();

	Physics physics(gameObjects, queue);
	Graphics graphics(w, gameObjects, queue);
	Input input(w, gameObjects, queue);
	Audio audio(queue);

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float msec = w.GetTimer()->GetTimedMS();
		input.InputUpdate(msec);
		physics.PhysicsUpdate(msec);
		graphics.GraphicsUpdate(msec);
		audio.AudioUpdate(msec);
	}



	delete queue, gameObjects;

	return 0;
}