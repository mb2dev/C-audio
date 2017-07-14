//
// Created by Mickael Bordage on 05/06/2017.
//

#ifndef C_AUDIO_SOUNDMANAGER_H
#define C_AUDIO_SOUNDMANAGER_H


#include <stdlib.h>
#include <stdio.h>
#include <iosfwd>
#include <fstream>
#include <unistd.h>
#include <string>
#include "fmod.hpp"

class soundManager {
public :
    soundManager();
    ~soundManager();
    FMOD::Sound * createSound(char * path, FMOD::Sound *sound);
    FMOD::Channel* playSound(FMOD::Sound *sound,FMOD::Channel *channel);
    unsigned int soundLength(FMOD::Sound *sound);
    unsigned int soundPlayPosition(FMOD::Channel *channel);
    void forward(unsigned int i,FMOD::Sound *sound,FMOD::Channel *channel);
    void backward(unsigned int i,FMOD::Sound *sound,FMOD::Channel *channel);
    void echo(FMOD::Channel *channel, FMOD::DSP *echo, float time);
    void removeEcho(FMOD::Channel *channel, FMOD::DSP *echo);
    void filterLowPass(FMOD::Channel *channel, FMOD::DSP *lowPass,int filter);
    void filterHightPass(FMOD::Channel *channel, FMOD::DSP *hightPass,int filter);
    void filterFlange(FMOD::Channel *channel, FMOD::DSP *hightPass,int filter);
    void compressor(FMOD::Channel *channel, FMOD::DSP *hightPass,int filter);
    void tone(FMOD::Channel *channel, FMOD::DSP *hightPass, float filter);


private :
    FMOD::System     *system;
};


#endif //C_AUDIO_SOUNDMANAGER_H
