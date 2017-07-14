//
// Created by Mickael Bordage on 05/06/2017.
//

#include <fmod.h>
#include <stddef.h>
#include "soundManager.h"



// init fmodEx sound
soundManager::soundManager() {
    FMOD_RESULT  resultFmod;
    resultFmod =FMOD::System_Create(&system);
    if (resultFmod != FMOD_OK)
    {
        printf("Create FMOD error  ! (%d) %s\n", resultFmod);
        exit(-1);
    }
    resultFmod = system->init(4, FMOD_INIT_NORMAL, NULL);
    if (resultFmod != FMOD_OK)
    {
        printf("FMOD error here! (%d) %s\n", resultFmod);
        exit(-1);
    }
}


// release fmodEx sound
soundManager::~soundManager(){
    //FMOD::System_Release(sys);
}


// allow to create a sound
FMOD::Sound * soundManager::createSound(char * path, FMOD::Sound *sound) {
    FMOD_RESULT       result;
    result = system->createSound(path, false, 0, &sound);
    if (result != FMOD_OK)
    {

        printf(" Create Sound FMOD error! (%d)\n", result);
        exit(-1);

    }
    return sound;

}



// allow to play a sound
FMOD::Channel* soundManager::playSound(FMOD::Sound *sound,FMOD::Channel *channel) {
    FMOD_RESULT  resultFmod;
    system->playSound(sound, 0, false, &channel);
    if (resultFmod != FMOD_OK)
    {

        printf(" Play Sound FMOD error! (%d)\n", resultFmod);
       exit(-1);
    }
    return channel;

}

// allow to get lenght of a sound
unsigned soundManager::soundLength(FMOD::Sound *sound){
    unsigned int i;
    sound->getLength(&i,FMOD_TIMEUNIT_MS);
    return i;
}

// allow to get current position
unsigned int soundManager::soundPlayPosition(FMOD::Channel *channel){
    unsigned int i;
    channel->getPosition(&i, FMOD_TIMEUNIT_MS);
    return i;
}

void soundManager::forward(unsigned int i,FMOD::Sound *sound,FMOD::Channel *channel) {
    unsigned int c=soundPlayPosition(channel);
    unsigned int l=soundLength(sound);
    if(c+i<l)
        channel->setPosition(c+i,FMOD_TIMEUNIT_MS);
}

void soundManager::backward(unsigned int i,FMOD::Sound *sound,FMOD::Channel *channel) {
    unsigned int c=soundPlayPosition(channel);
    if(c-i>0)
        channel->setPosition(c-i,FMOD_TIMEUNIT_MS);
}

void soundManager::echo(FMOD::Channel *channel, FMOD::DSP *echo, float time) {
    system->createDSPByType(FMOD_DSP_TYPE_ECHO,  &echo);
    echo->setParameterFloat(FMOD_DSP_ECHO_DELAY, time);
    channel->addDSP(0,echo);
}

void soundManager::removeEcho(FMOD::Channel *channel, FMOD::DSP *echo) {
    channel->removeDSP(echo);
}

void soundManager::filterLowPass(FMOD::Channel *channel, FMOD::DSP *lowPass, int filter) {
    system->createDSPByType(FMOD_DSP_TYPE_LOWPASS,&lowPass);
    lowPass->setParameterInt(FMOD_DSP_LOWPASS_CUTOFF, filter);
    channel->addDSP(0,lowPass);
}

void soundManager::filterHightPass(FMOD::Channel *channel, FMOD::DSP *hightPass, int filter) {
    system->createDSPByType(FMOD_DSP_TYPE_LOWPASS,&hightPass);
    hightPass->setParameterInt(FMOD_DSP_LOWPASS_CUTOFF, filter);
    channel->addDSP(0,hightPass);
}

void soundManager::filterFlange(FMOD::Channel *channel, FMOD::DSP *flange, int filter) {
    system->createDSPByType(FMOD_DSP_TYPE_FLANGE,&flange);
    flange->setParameterInt(FMOD_DSP_FLANGE_RATE,filter);
    channel->addDSP(0,flange);
}
void soundManager::compressor(FMOD::Channel *channel, FMOD::DSP *compressor, int filter) {
    system->createDSPByType(FMOD_DSP_TYPE_COMPRESSOR, &compressor);
    compressor->setParameterInt(FMOD_DSP_COMPRESSOR_ATTACK,1000);
    channel->addDSP(0,compressor);
}

void soundManager::tone(FMOD::Channel *channel, FMOD::DSP *tone, float filter) {
   system->createDSPByType(FMOD_DSP_TYPE_OSCILLATOR, &tone);
   tone->setParameterFloat(FMOD_DSP_OSCILLATOR_RATE,filter);

    channel->addDSP(0,tone);


}


