#include "GameLoader.h"



GameLoader::GameLoader(std::string gameInfo, std::vector<GameObject*>& objects)
{
	this->gameInfo = gameInfo;
	objList = &objects;

	std::ifstream level;
	level.open(gameInfo);

	std::string testInfo[9][10];
	
	if (level) {
		std::string firstLine;
		int line = 0;
		int heading = 0;

		while (std::getline(level, firstLine)) {
			std::stringstream test(firstLine);
			while (test.good()) {
				std::string substr;
				std::getline(test, substr, ',');
				
				testInfo[heading][line] = substr;
				heading++;
				if (heading == 9)
					heading = 0;
			}
			line++;
			if (line == 10)
				line = 0;
		}

	}

	level.close();


	for (int i = 1; i < 10; ++i) {
		for (int j = 1; j < 9; ++j) {
			

			std::cout << testInfo[j][i] << std::endl;
		}
		std::string::size_type sz;
		objList->push_back(new GameObject(std::stof(testInfo[2][i],&sz), std::stof(testInfo[3][i], &sz), std::stof(testInfo[4][i], &sz), std::stof(testInfo[5][i], &sz), std::stof(testInfo[6][i], &sz), std::stof(testInfo[7][i], &sz), testInfo[0][i], testInfo[1][i], testInfo[8][i]));
	}

}


GameLoader::~GameLoader()
{
}
