#include "gvmainwindow.h"
#include <QGridLayout>
#include <QMenuBar>
#include <QPluginLoader>

GVMainWindow::GVMainWindow(QWidget *parent) : QMainWindow(parent)
{
    createUi();
    connectUi();
}

void GVMainWindow::createUi()
{
    ///////////MENU///////////////////////
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);

    /////////CENTRAL WIDGET//////////////

    QGridLayout *grid = new QGridLayout;
    p_a = new AudioSection(0, 0);
    p_b = new AudioSection(0, 1);
    browser = new FileBrowser;

    grid->addWidget(p_a, 0, 0);
    grid->addWidget(p_b, 0, 1);
    grid->addWidget(browser, 1, 0);

    QWidget *centralW = new QWidget;
    centralW->setLayout(grid);

    this->setCentralWidget(centralW);
}

void GVMainWindow::connectUi()
{

}

bool GVMainWindow::loadPlugin()
{
    qDebug("appDirPath = "+qApp->applicationDirPath().toLatin1());
    QDir pluginsDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        qDebug(fileName.toLatin1());
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            this->fxInterface = qobject_cast<FXInterface *>(plugin);
            if (this->fxInterface)
                return true;
        }
    }

    return false;
}//loadPlugin
