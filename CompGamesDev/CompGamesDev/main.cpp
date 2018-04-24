#include <nclgl\Window.h>
#include "Renderer.h"
#include <Common\EventQueue.h>
#include <Renderer\Graphics.h>
#include <Physics\Physics.h>
#include <Input\Input.h>
#include <Audio\Audio.h>
#include <FileIO\GameLoader.h>
#include <Profiler\Profiling.h>


int main() {

	//Create a windo
	Window w("CSC3224 - Game Engine", 1920, 1080);

	//Create a store for the game objects
	vector<GameObject*> gameObjects;

	//load the game from csv and give it the game objects vector
	GameLoader("..\\TestLevel\\test.csv", gameObjects);

	//Create an event queue
	EventQueue* queue = new EventQueue();

	//Create each subsystem and give it what it needs
	Physics physics(gameObjects, queue);
	Graphics graphics(w, gameObjects, queue);
	Input input(w, gameObjects, queue);
	Audio audio(queue);

	Profiling profiler;

	

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		//get msec
		float msec = w.GetTimer()->GetTimedMS();

		//Update each system and get how long that system took to run
		float currentTime = w.GetTimer()->GetMS();
		input.InputUpdate(msec);
		float inputTime = w.GetTimer()->GetMS() - currentTime;

		currentTime = w.GetTimer()->GetMS();
		audio.AudioUpdate(msec);
		float audioTime = w.GetTimer()->GetMS() - currentTime;

		currentTime = w.GetTimer()->GetMS();
		physics.PhysicsUpdate(msec);
		float physicsTime = w.GetTimer()->GetMS() - currentTime;

		currentTime = w.GetTimer()->GetMS();
		graphics.GraphicsUpdate(msec);
		float graphicsTime = w.GetTimer()->GetMS() - currentTime;


		
		//Update the profiler with the times of each system
		profiler.profilerUpdate(msec, inputTime, physicsTime, graphicsTime, audioTime);

	}


	//delete objects
	delete queue, gameObjects;

	return 0;
}