#ifndef GVMAINWINDOW_H
#define GVMAINWINDOW_H

#include <QMainWindow>
#include "audiosection.h"
#include "shazamsection.h"
#include "filebrowser.h"
#include "fxinterface.h"

class GVMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GVMainWindow(QWidget *parent = 0);

protected:
    AudioSection *p_a, *p_b;
    FileBrowser *browser;

private:
    bool GVMainWindow::loadPlugin();
    FXInterface *fxInterface;
    void createUi();
    void connectUi();

signals:

public slots:
};

#endif // GVMAINWINDOW_H
