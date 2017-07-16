//
// Created by Mickael Bordage on 05/06/2017.
//

#include "soundmanager.h"
#include<QDebug>

// init fmodEx sound
SoundManager::SoundManager()
{
    result = FMOD::System_Create(&system);
    if (result != FMOD_OK)
    {
        qDebug("Create FMOD error  ! (%d) %s\n", result);
        exit(-1);
    }
    result = system->init(4, FMOD_INIT_NORMAL, NULL);
    if (result != FMOD_OK)
    {
        qDebug("FMOD error here! (%d) %s\n", result);
        exit(-1);
    }
    qDebug("system in manager %p", system);
//    player_a = SoundPlayer(system);
//    player_b = SoundPlayer(system);
    player_a = new SoundPlayer(system);
    player_b = new SoundPlayer(system);
}

// release fmodEx sound
SoundManager::~SoundManager(){
    system->release();
}
