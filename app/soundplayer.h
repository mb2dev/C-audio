#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include "fmod.hpp"

class SoundPlayer
{
public:
    SoundPlayer();
    SoundPlayer(FMOD::System *sys);
    ~SoundPlayer();
    FMOD::Sound* load(char * path);
    FMOD::Channel* play();
    unsigned int getLength();
    unsigned int getPlayPosition();
    void forward(unsigned int i);
    void backward(unsigned int i);
    void stop();
    void echo(float time);
    void removeEcho();
    void filterLowPass(int filter);
    void filterHighPass(int filter);
    void filterFlange(int filter);
    void compressor(int filter);
    void tone(float filter);
protected:
    FMOD::System *system;
    FMOD::Sound *sound;
    FMOD::DSP *dsp_echo;
    FMOD::DSP *dsp_high_pass;
    FMOD::DSP *dsp_low_pass;
    FMOD::DSP *dsp_flange;
    FMOD::DSP *dsp_compressor;
    FMOD::DSP *dsp_tone;
    FMOD::Channel *channel = 0;
    FMOD_RESULT result;
};

#endif // SOUNDPLAYER_H
