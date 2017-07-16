#include <QApplication>
#include "gvmainwindow.h"
#include "soundmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Audio Mixer");
    GVMainWindow w;
    w.show();

    SoundManager manager;

    QByteArray ba = app.applicationDirPath().toLatin1() + "/../drumloop.wav";
    char *c_str = ba.data();

    manager.player_a->load(c_str);
    manager.player_a->play();

    return app.exec();
}
