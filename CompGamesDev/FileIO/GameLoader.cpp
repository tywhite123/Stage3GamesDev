#include "GameLoader.h"



GameLoader::GameLoader(std::string gameInfo, std::vector<GameObject*>& objects)
{
	//Assign the information
	this->gameInfo = gameInfo;
	objList = &objects;

	//Create a file stream and open the file
	std::ifstream level;
	level.open(gameInfo);

	//Setup the array for the information
	std::string testInfo[9][10];
	
	//check if file is open
	if (level) {

		//Get the first line
		std::string firstLine;

		//variable to put in the info in the correct place in the info array
		int line = 0;
		int heading = 0;

		//While you there is a line
		while (std::getline(level, firstLine)) {

			//Split it into each component by the comma
			std::stringstream test(firstLine);
			while (test.good()) {
				std::string substr;
				std::getline(test, substr, ',');
				
				//Stick that into the info array
				testInfo[heading][line] = substr;

				//increment heading
				heading++;

				//if heading is at 9 restart
				if (heading == 9)
					heading = 0;
			}

			//increment line
			line++;

			//if at 10 restart
			if (line == 10)
				line = 0;
		}

	}

	//Close file
	level.close();


	for (int i = 1; i < 10; ++i) {
		/*for (int j = 1; j < 9; ++j) {
			

			std::cout << testInfo[j][i] << std::endl;
		}*/
		//for each line create a game object for it
		std::string::size_type sz;
		objList->push_back(new GameObject(std::stof(testInfo[2][i],&sz), std::stof(testInfo[3][i], &sz), std::stof(testInfo[4][i], &sz), std::stof(testInfo[5][i], &sz), std::stof(testInfo[6][i], &sz), std::stof(testInfo[7][i], &sz), testInfo[0][i], testInfo[1][i], testInfo[8][i]));
	}

}


GameLoader::~GameLoader()
{
}
