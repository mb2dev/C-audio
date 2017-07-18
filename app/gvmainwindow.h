#ifndef GVMAINWINDOW_H
#define GVMAINWINDOW_H

#include <QMainWindow>
#include "audiosection.h"
#include "shazamsection.h"
#include "filebrowser.h"
#include "fxinterface.h"
#include "soundmanager.h"

class GVMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GVMainWindow(QWidget *parent = 0);
    ~GVMainWindow();
protected:
    AudioSection *p_a, *p_b;
    FileBrowser *browser;

private:
    bool GVMainWindow::loadPlugin();
    FXInterface *fxInterface;
    void createUi();
    void connectUi();
    SoundManager* m_soundmanager;

signals:

public slots:
    void loadSong(int index, QString filePath);
};

#endif // GVMAINWINDOW_H
