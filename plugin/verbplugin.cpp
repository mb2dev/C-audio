#include "verbplugin.h"
#include "fmod.hpp"

VerbPlugin::VerbPlugin(QObject *parent)
    : QObject(parent)
{
    m_name = "Reverb";
    m_type = FMOD_DSP_TYPE_SFXREVERB;
    m_paramsIndex = QVector<int>() << 1;
    m_paramsName = QVector<QString>();
}

VerbPlugin::~VerbPlugin(){}

void VerbPlugin::apply() const{

}

QString VerbPlugin::getName() const {
    return m_name;
}
