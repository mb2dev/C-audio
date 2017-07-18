#include "soundplayer.h"
#include <QDebug>


SoundPlayer::SoundPlayer(){
    system = nullptr;
}

SoundPlayer::SoundPlayer(FMOD::System *sys)
    : system(sys)
{
    qDebug("system object %p", system);

}

void SoundPlayer::initFX(){
    system->createDSPByType(FMOD_DSP_TYPE_ECHO,  &dsp_echo);
    channel->addDSP(0, dsp_echo);
    dsp_echo->setBypass(true);

//    system->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &dsp_low_pass);
//    channel->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, dsp_low_pass);
//    dsp_low_pass->setBypass(true);

//    system->createDSPByType(FMOD_DSP_TYPE_HIGHPASS,&dsp_high_pass);
//    channel->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, dsp_high_pass);
//    dsp_low_pass->setBypass(true);

    system->createDSPByType(FMOD_DSP_TYPE_THREE_EQ, &dsp_three_eq);
    channel->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, dsp_three_eq);

//    system->createDSPByType(FMOD_DSP_TYPE_FLANGE,&dsp_flange);
//    channel->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, dsp_flange);

//    system->createDSPByType(FMOD_DSP_TYPE_COMPRESSOR, &dsp_compressor);
//    channel->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, dsp_compressor);

//    system->createDSPByType(FMOD_DSP_TYPE_OSCILLATOR, &dsp_tone);
//    channel->addDSP(FMOD_CHANNELCONTROL_DSP_HEAD, dsp_tone);
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
    bool paused, isplaying;
    channel->getPaused(&paused);
    channel->isPlaying(&isplaying);
    qDebug("is paused %d", paused);
    if(loaded && paused){
        channel->setPaused(false);
    }else if(!loaded){
        result = system->playSound(sound, 0, false, &channel);
        if (result != FMOD_OK)
        {
           qDebug(" Play Sound FMOD error! (%d)\n", result);
        }else{
            loaded = true;
            initFX();
        }
    }
    return channel;
}

void SoundPlayer::stop() {
    result = channel->setPaused(true);
    if (result != FMOD_OK)
    {
       qDebug("Stop FMOD error! (%d)\n", result);
    }
}

void SoundPlayer::setVolume(float volume){
    if(!loaded){
        return;
    }

    result = channel->setVolume(volume);
    if (result != FMOD_OK)
    {
       qDebug("SetVolume FMOD error! (%d)\n", result);
    }
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

// paramValue from 0 to 100
void SoundPlayer::echo(int paramIndex, int paramValue) {
    float v;
    if(paramIndex == FMOD_DSP_ECHO_DELAY){
        v = ((float)paramValue)/100.0f * 4990.0f + 10.0f;
    }
    if(paramIndex == FMOD_DSP_ECHO_DRYLEVEL){
        v = ((float)paramValue)/100.0f * 90.0f - 80.0f;
    }
    if(paramIndex == FMOD_DSP_ECHO_FEEDBACK){
       v = (float)paramValue;
    }
    dsp_echo->setParameterInt(paramIndex, paramValue);
}

void SoundPlayer::removeEcho() {
    channel->removeDSP(dsp_echo);
}

// from -80.0 to 10.0
void SoundPlayer::filter(FMOD_DSP_THREE_EQ eq, float db)
{
    qDebug() << "EQ TYPE" << eq << "db : " << db;
    result = dsp_three_eq->setParameterFloat(eq, db);
    if (result != FMOD_OK)
    {
       qDebug("filter FMOD error! (%d)\n", result);
    }
}

void SoundPlayer::filterLowPass(int filter)
{
    dsp_low_pass->setParameterInt(FMOD_DSP_LOWPASS_CUTOFF, filter);
}

void SoundPlayer::filterHighPass(int filter)
{
    dsp_high_pass->setParameterInt(FMOD_DSP_HIGHPASS_CUTOFF, filter);
}

void SoundPlayer::filterFlange(int filter)
{
    dsp_flange->setParameterInt(FMOD_DSP_FLANGE_RATE,filter);
}

void SoundPlayer::compressor()
{
    dsp_compressor->setParameterInt(FMOD_DSP_COMPRESSOR_ATTACK,1000);
}

void SoundPlayer::tone(float filter)
{
   dsp_tone->setParameterFloat(FMOD_DSP_OSCILLATOR_RATE,filter);
}
