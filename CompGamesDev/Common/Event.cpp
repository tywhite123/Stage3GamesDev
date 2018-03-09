#include "Event.h"



Event::Event(GameEnums::MType type)
{
	eventType = type;

	if (eventType == GameEnums::MType::Move_Left) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}

	if (eventType == GameEnums::MType::Move_Right) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::Move_Up) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::Move_Down) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	/*if (eventType == GameEnums::MType::Face_Down) {
		//subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::Face_Left) {
		//subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::Face_Right) {
		//subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::Move_Up) {
		//subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}*/

}


Event::~Event()
{
}
