#ifndef FXINTERFACE_H
#define FXINTERFACE_H
#include <QtPlugin>
#include <QVector>
#include "fmod.hpp"

class QString;

class FXInterface {

public:
    virtual ~FXInterface(){}
    virtual void apply() const = 0;
    virtual QString getName() const = 0;
    QString m_name;
    FMOD_DSP_TYPE m_type;
    QVector<int> m_paramsIndex;
    QVector<QString> m_paramsName;
private:
};

#define FXInterface_iid "com.gabrievv.esgi.cpp.FXInterface"

Q_DECLARE_INTERFACE(FXInterface, FXInterface_iid)

#endif // FXINTERFACE_H
