#include <QApplication>
#include "gvmainwindow.h"
#include "soundmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Audio Mixer");
    GVMainWindow w;
    w.show();

    return app.exec();
}
