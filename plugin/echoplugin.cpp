#include "echoplugin.h"
#include "fmod.hpp"

EchoPlugin::EchoPlugin(QObject *parent)
    : QObject(parent)
{
    m_name = "Echo";
    m_type = FMOD_DSP_TYPE_ECHO;
    m_paramsIndex = QVector<int>() << 1;
    m_paramsName = QVector<QString>();
}

EchoPlugin::~EchoPlugin(){}

void EchoPlugin::apply() const{

}

QString EchoPlugin::getName() const {
    return m_name;
}
