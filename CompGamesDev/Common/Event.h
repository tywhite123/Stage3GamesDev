#pragma once

#include <vector>

namespace GameEnums {
	enum Subsystem {
		Physics, Graphics, Input, Audio, IO
	};

	//Replace face and move into the same thing
	enum MType {
		Move_Left, Move_Right, Move_Up, Move_Down, New_Obj, Rest, Update_Pos_AI
	};
};

class Event
{
public:
	Event(GameEnums::MType type);
	~Event();

	
	GameEnums::MType getType() { return eventType; }
	std::vector<GameEnums::Subsystem> getSubsystems() { return subsystems; }



protected:
	//bool eventFinished;
	GameEnums::MType eventType;
	std::vector<GameEnums::Subsystem> subsystems;

};

