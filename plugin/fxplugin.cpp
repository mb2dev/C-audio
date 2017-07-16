#include "fxplugin.h"

FXPlugin::FXPlugin(){
    m_Name = "SoundFX";
}

FXPlugin::~FXPlugin(){}

void FXPlugin::apply() const{

}

QString FXPlugin::getName() const {
    return m_Name;
}

