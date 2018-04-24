#include "Audio.h"



Audio::Audio(EventQueue* eq)
{
	eQueue = eq;

	//Create a system for FMOD sound
	result = FMOD::System_Create(&system);
	
	//Check you have the correct version
	result = system->getVersion(&version);

	if (version < FMOD_VERSION) {
		return;
	}

	//Initialise the system
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);

	//Create some sounds by getting the audio file
	result = system->createSound("..\\Audio\\drumloop.wav", FMOD_DEFAULT, 0, &soundTest);
	result = system->createSound("..\\Audio\\sword.wav", FMOD_DEFAULT, 0, &sword);

	//Set it so the audio doesnt loop
	result = soundTest->setMode(FMOD_LOOP_OFF);

}


Audio::~Audio()
{

	//Close and release everythingh
	result = soundTest->release();
	result = sword->release();
	result = system->close();
	result = system->release();
}

void Audio::AudioUpdate(float msec)
{

	/*if (!playing) {
		result = system->playSound(soundTest, 0, false, &channel);
	}*/

	
	//Check for events
	RecieveEvent();

	//update the system
	result = system->update();

}

void Audio::RecieveEvent()
{
	//Check each event and subsytem assigned to that event
	for (int i = 0; i < eQueue->getEvents().size(); ++i) {
		//if(eQueue->getEvents().at(i)->getSubsystems())
		for (int j = 0; j < eQueue->getEvents().at(i)->getSubsystems().size(); ++j) {
			
			//Check if correct subsystem
			if (eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {

				//Check is the event type correct
				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Attack) {
					
					//Check to see if sound is already playing
					if (!playing)
						//play sound
						result = system->playSound(sword, 0, false, &channel);


					result = channel->isPlaying(&playing);
				}

			}

				


			//Pop the event off the queue
			if (eQueue->getEvents().at(i)->getSubsystems().size() - 1 == j
				&& eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {
				eQueue->popEvent();
				return;
			}
		}

	}
	

}
