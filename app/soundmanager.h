#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "fmod.hpp"
#include "soundplayer.h"
#include <QObject>

class SoundManager : public QObject {

    Q_OBJECT

public :
    explicit SoundManager(QObject *parent = 0);
    ~SoundManager();

    SoundPlayer *player_a, *player_b;
protected:
    FMOD_RESULT result;

private :
    FMOD::System *system;

//public slots:
//    void startPlayback(const int player);
//    void suspend(const int player);

};

#endif // SOUNDMANAGER_H
