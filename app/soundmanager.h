#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "fmod.hpp"
#include "soundplayer.h"

class SoundManager {

public :
    SoundManager();
    ~SoundManager();

    SoundPlayer *player_a, *player_b;
protected:
    FMOD_RESULT result;

private :
    FMOD::System *system;

};

#endif // SOUNDMANAGER_H
