#include "fxplugin.h"
#include "fmod.hpp"

FXPlugin::FXPlugin(QObject *parent)
    : QObject(parent)
{
    m_name = "Echo";
    m_type = FMOD_DSP_TYPE_ECHO;
    m_paramsIndex = QVector<int>() << FMOD_DSP_ECHO_DRYLEVEL << FMOD_DSP_ECHO_DELAY << FMOD_DSP_ECHO_FEEDBACK;
    m_paramsName = QVector<QString>() << "Dry Level" << "Delay" << "Feedback";
}

FXPlugin::~FXPlugin(){}

void FXPlugin::apply() const{

}

QString FXPlugin::getName() const {
    return m_name;
}

