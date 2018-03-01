#pragma once

#include <string>
#include "GameObject.h"
#include <vector>

namespace GameEnums {


	enum Subsystem {
		Physics, Graphics, Input, Audio, IO
	};

	enum MType {
		Spawn_Tri
	};
};

class GameObject;

class Message
{
public:
	/*Message(GameEnums::Subsystem to, GameEnums::Subsystem from, GameEnums::MType type, float data);
	Message(GameEnums::Subsystem to, GameEnums::MType type, float data);
	~Message();

	GameEnums::Subsystem GetTo() { return to; }*/

	Message() {}
	Message(GameEnums::MType type);
	~Message();

	/*std::vector<GameEnums::Subsystem> getSubsystems() const{
		return sysDeliv;
	}*/

	GameEnums::MType getType() const { return mType; }
	GameEnums::Subsystem getSys() const { return sys; }

protected:
	GameEnums::MType mType;
	//std::vector<GameEnums::Subsystem> sysDeliv;
	GameEnums::Subsystem sys;

	/*GameEnums::Subsystem to;
	GameEnums::Subsystem from;
	GameEnums::MType type;
	float data;*/
};

