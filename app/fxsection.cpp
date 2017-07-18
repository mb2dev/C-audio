#include "fxsection.h"
#include <QLabel>
#include <QDir>
#include <QPluginLoader>

FXSection::FXSection(QString appPath, QWidget *parent)
    : QWidget(parent)
    , m_appPath(appPath)
    , m_param_one(new QDial(this))
    , m_param_two(new QDial(this))
    , m_param_three(new QDial(this))
    , m_combo(new QComboBox(this))
    , m_layout(new QGridLayout)
{
    createUi();
    connectUi();
}

void FXSection::createUi()
{
    m_param_one->setMaximum(100);
    m_param_two->setMaximum(100);
    m_param_three->setMaximum(100);

    m_param_one->setMinimum(0);
    m_param_two->setMinimum(0);
    m_param_three->setMinimum(0);

    m_param_one->setSliderPosition(50);
    m_param_two->setSliderPosition(50);
    m_param_three->setSliderPosition(50);

    if(loadPlugin()){
        m_combo->addItem(fxInterface->getName());
        m_paramOne = new QLabel(fxInterface->m_paramsName[0]);
        m_paramTwo = new QLabel(fxInterface->m_paramsName[1]);
        m_paramThree = new QLabel(fxInterface->m_paramsName[2]);
        emit fxSelected(fxInterface);
    }else{
        m_paramOne = new QLabel("Param 1");
        m_paramTwo = new QLabel("Param 2");
        m_paramThree = new QLabel("Param 3");
    }

    m_layout->addWidget(m_combo, 0, 0, 2, 1);

    m_layout->addWidget(m_param_one, 0, 1);

    m_paramOne->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_layout->addWidget(m_paramOne, 1, 1);

    m_layout->addWidget(m_param_two, 0, 2);

    m_paramTwo->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_layout->addWidget(m_paramTwo, 1, 2);

    m_layout->addWidget(m_param_three, 0, 3);
    m_paramThree->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_layout->addWidget(m_paramThree, 1, 3);

    this->setLayout(m_layout);
    //this->setStyleSheet("background-color : red");
}

void FXSection::connectUi()
{
    connect(m_param_one, SIGNAL(valueChanged(int)), this, SLOT(paramOneChanged(int)));
    connect(m_param_two, SIGNAL(valueChanged(int)), this, SLOT(paramTwoChanged(int)));
    connect(m_param_three, SIGNAL(valueChanged(int)), this, SLOT(paramThreeChanged(int)));
}

void FXSection::paramOneChanged(int sliderValue){
    emit valueChanged(fxInterface->m_type, fxInterface->m_paramsIndex[0], sliderValue);
}

void FXSection::paramTwoChanged(int sliderValue){
    emit valueChanged(fxInterface->m_type, fxInterface->m_paramsIndex[1], sliderValue);
}

void FXSection::paramThreeChanged(int sliderValue){
    emit valueChanged(fxInterface->m_type, fxInterface->m_paramsIndex[2], sliderValue);
}

bool FXSection::loadPlugin()
{
    QDir pluginsDir(m_appPath);
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
