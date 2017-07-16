#include "soundplayer.h"
#include <QDebug>


SoundPlayer::SoundPlayer(){
    system = nullptr;
}

SoundPlayer::SoundPlayer(FMOD::System *sys) : system(sys)
{
    qDebug("system object %p", system);
}

SoundPlayer::~SoundPlayer()
{
    delete dsp_echo;
    delete dsp_tone;
    delete dsp_high_pass;
    delete dsp_low_pass;
    delete dsp_compressor;
    delete dsp_flange;
    delete channel;
    delete sound;
}

/**
 * allow to create a sound
 * http://www.fmod.org/documentation/#content/generated/FMOD_System_CreateSound.html
 */
FMOD::Sound * SoundPlayer::load(char* path) {
    qDebug("path: %s", path);
    result = system->createSound(path, false, 0, &sound);
    if (result != FMOD_OK)
    {
        qDebug("Create Sound FMOD error! (%d)\n", result);
    }
    return sound;
}

// allow to play a sound
FMOD::Channel* SoundPlayer::play() {
    system->playSound(sound, 0, false, &channel);
    if (result != FMOD_OK)
    {
       qDebug(" Play Sound FMOD error! (%d)\n", result);
    }
    return channel;
}

// allow to get lenght of a sound
unsigned SoundPlayer::getLength(){
    unsigned int i;
    sound->getLength(&i,FMOD_TIMEUNIT_MS);
    return i;
}

// allow to get current position
unsigned int SoundPlayer::getPlayPosition(){
    unsigned int i;
    channel->getPosition(&i, FMOD_TIMEUNIT_MS);
    return i;
}

void SoundPlayer::forward(unsigned int i) {
    unsigned int c = getPlayPosition();
    unsigned int l = getLength();
    if(c+i<l)
        channel->setPosition(c+i,FMOD_TIMEUNIT_MS);
}

void SoundPlayer::backward(unsigned int i) {
    unsigned int c = getPlayPosition();
    if(c-i>0)
        channel->setPosition(c-i,FMOD_TIMEUNIT_MS);
}

void SoundPlayer::echo(float time) {
    system->createDSPByType(FMOD_DSP_TYPE_ECHO,  &dsp_echo);
    dsp_echo->setParameterFloat(FMOD_DSP_ECHO_DELAY, time);
    channel->addDSP(0, dsp_echo);
}

void SoundPlayer::removeEcho() {
    channel->removeDSP(dsp_echo);
}

void SoundPlayer::filterLowPass(int filter) {
    system->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &dsp_low_pass);
    dsp_low_pass->setParameterInt(FMOD_DSP_LOWPASS_CUTOFF, filter);
    channel->addDSP(0,dsp_low_pass);
}

void SoundPlayer::filterHighPass(int filter) {
    system->createDSPByType(FMOD_DSP_TYPE_LOWPASS,&dsp_high_pass);
    dsp_high_pass->setParameterInt(FMOD_DSP_LOWPASS_CUTOFF, filter);
    channel->addDSP(0,dsp_high_pass);
}

void SoundPlayer::filterFlange(int filter) {
    system->createDSPByType(FMOD_DSP_TYPE_FLANGE,&dsp_flange);
    dsp_flange->setParameterInt(FMOD_DSP_FLANGE_RATE,filter);
    channel->addDSP(0,dsp_flange);
}
void SoundPlayer::compressor(int filter) {
    system->createDSPByType(FMOD_DSP_TYPE_COMPRESSOR, &dsp_compressor);
    dsp_compressor->setParameterInt(FMOD_DSP_COMPRESSOR_ATTACK,1000);
    channel->addDSP(0,dsp_compressor);
}

void SoundPlayer::tone(float filter) {
   system->createDSPByType(FMOD_DSP_TYPE_OSCILLATOR, &dsp_tone);
   dsp_tone->setParameterFloat(FMOD_DSP_OSCILLATOR_RATE,filter);
   channel->addDSP(0,dsp_tone);
}
