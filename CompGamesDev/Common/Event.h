#pragma once

#include <vector>

//Enums for subsystems and event type
namespace GameEnums {
	enum Subsystem {
		Physics, Graphics, Input, Audio, IO
	};

	//Replace face and move into the same thing
	enum MType {
		Move_Left, Move_Right, Move_Up, Move_Down, New_Obj, Rest, Update_Pos_AI, Attack, Input_Time, Audio_Time, Physics_Time, Graphics_Time, New_Level, Finish_Level
	};
};

class Event
{
public:
	Event(GameEnums::MType type);
	Event(GameEnums::MType type, bool newLvl, float data);
	~Event();

	//Get information about the event
	GameEnums::MType getType() { return eventType; }
	bool newLevel() { return levelNew; }
	float getData() { return data; }
	std::vector<GameEnums::Subsystem> getSubsystems() { return subsystems; }



protected:
	//bool eventFinished;
	//event info variables
	GameEnums::MType eventType;
	std::vector<GameEnums::Subsystem> subsystems;

	float data;

	bool levelNew;
};

