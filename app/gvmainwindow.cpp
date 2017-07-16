#include "gvmainwindow.h"
#include <QGridLayout>
#include <QMenuBar>
#include <QPluginLoader>
#include "soundmanager.h"

GVMainWindow::GVMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_soundmanager(new SoundManager)
{
    createUi();
    connectUi();
}

GVMainWindow::~GVMainWindow()
{
    delete m_soundmanager;
}

void GVMainWindow::createUi()
{
    ///////////MENU///////////////////////
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);

    /////////CENTRAL WIDGET//////////////

//    QGridLayout *grid = new QGridLayout;
    p_a = new AudioSection(0, 0, m_soundmanager);
    p_b = new AudioSection(0, 1, m_soundmanager);
    browser = new FileBrowser;

    QHBoxLayout *hbl_top = new QHBoxLayout;
    hbl_top->addWidget(p_a);
    hbl_top->addWidget(p_b);

    QVBoxLayout *hbl_bottom = new QVBoxLayout;
    hbl_bottom->addWidget(browser);
    hbl_bottom->addWidget(new QSlider(Qt::Horizontal));

    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addLayout(hbl_top);
    vbl->addLayout(hbl_bottom);
//    grid->addWidget(p_a, 0, 0, 1, 2, Qt::AlignHCenter);
//    grid->addWidget(p_b, 0, 3, 1, 2, Qt::AlignHCenter);
//    grid->addWidget(new QSlider(Qt::Horizontal), 1, 2, 1, 1);
//    grid->addWidget(browser, 1, 0, 1, 2);
//    grid->addWidget(new QWidget(this), 1, 3, 1, 2);

    QWidget *centralW = new QWidget;
    centralW->setLayout(vbl);

    this->setCentralWidget(centralW);
}

void GVMainWindow::connectUi()
{
    connect(browser, SIGNAL(songToLoad(int,QString)), this, SLOT(loadSong(int, QString)));
    connect(browser, SIGNAL(songToLoad(int,QString)), p_a, SLOT(loadFile(int, QString)));
    connect(browser, SIGNAL(songToLoad(int,QString)), p_b, SLOT(loadFile(int, QString)));
}

void GVMainWindow::loadSong(int index, QString filePath){
    qDebug("loadSong "+filePath.toLatin1());

    QByteArray ba = filePath.toLatin1();
    char *c_str = ba.data();
    if(index == 0){
        m_soundmanager->player_a->load(c_str);
        //p_a->m_waveform->
    }else{
        m_soundmanager->player_b->load(c_str);
    }
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
