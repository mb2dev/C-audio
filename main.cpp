#include <stdlib.h>
#include <stdio.h>
#include <iosfwd>
#include <fstream>
#include <unistd.h>
#include "fmod.hpp"
#include "soundManager/soundManager.h"

int main()
{
    // create son system
    //FMOD::System     *system;
    FMOD::Sound      *sound1, *sound2, *sound3;
    FMOD::DSP *echo;
    FMOD::DSP *hight_pass;
    FMOD::DSP *low_pass;
    FMOD::DSP *flange;
    FMOD::DSP *compressor;
    FMOD::DSP *tone;
    FMOD::Channel    *channel = 0;
    FMOD_RESULT       result;


    soundManager sound;
    sound1 = sound.createSound("/Users/Mickael/Documents/ProjectESGI/C-audio/pan.wav", sound1);
    channel = sound.playSound(sound1, channel);
    printf("%d", sound.soundLength(sound1));
    sleep(5);
    printf(" %d", sound.soundPlayPosition(channel));
    sound.forward(20000,sound1,channel);
    printf("%d", sound.soundPlayPosition(channel));
    sleep(5);
    sound.backward(20000,sound1,channel);
    printf(" %d", sound.soundPlayPosition(channel));
   // sound.echo(channel,echo,0.5);
   // sleep(5);
   // sound.removeEcho(channel,echo);
   // sleep(5);
   // sound.filterHightPass(channel,hight_pass,0);
    sleep(5);
   // sound.filterLowPass(channel,low_pass,0);
    sound.filterFlange(channel,flange,100);
   // sound.compressor(channel,compressor,10);
   // sound.tone(channel,tone, 440.0f);

    sleep(5000);


    return 0;
}
