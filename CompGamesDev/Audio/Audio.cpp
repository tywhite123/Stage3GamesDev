#include "Audio.h"



Audio::Audio(EventQueue* eq)
{
	eQueue = eq;

	
	result = FMOD::System_Create(&system);
	
	result = system->getVersion(&version);

	if (version < FMOD_VERSION) {
		
	}

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);

	result = system->createSound("..\\Audio\\drumloop.wav", FMOD_DEFAULT, 0, &soundTest);

	result = soundTest->setMode(FMOD_LOOP_OFF);

}


Audio::~Audio()
{

	result = soundTest->release();
	result = system->close();
	result = system->release();
}

void Audio::AudioUpdate(float msec)
{

	result = system->playSound(soundTest, 0, false, &channel);

	result = system->update();

}
