#pragma once

#include <Common\GameObject.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

class GameLoader
{
public:
	GameLoader(std::string gameInfo, std::vector<GameObject*>& objects);
	~GameLoader();

private:
	std::string gameInfo;
	std::vector<GameObject*>* objList;
};

