#include "Event.h"



Event::Event(GameEnums::MType type)
{
	eventType = type;

	if (eventType == GameEnums::MType::Move_Left) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		//subsystems.push_back(GameEnums::Subsystem::Graphics);
	}

	if (eventType == GameEnums::MType::Move_Right) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		//subsystems.push_back(GameEnums::Subsystem::Graphics);
	}

}


Event::~Event()
{
}
