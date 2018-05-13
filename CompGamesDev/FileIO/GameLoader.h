#pragma once

#include <Common\GameObject.h>
#include <Common\EventQueue.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

class GameLoader
{
public:
	GameLoader(std::string gameInfo, std::vector<GameObject*>& objects, EventQueue* eQueue);
	~GameLoader();

	void LoadLevel(std::string gameInfo);

private:

	//Information for game loader
	std::string gameInfo;
	std::vector<GameObject*>* objList;
	EventQueue* eQueue;
};

