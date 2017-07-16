#ifndef FXPLUGIN_H
#define FXPLUGIN_H

#include "fxinterface.h"

// @see http://doc.qt.io/qt-5/qtplugin.html

class FXPlugin : public QObject, public FXInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.gabrievv.esgi.cpp.FXInterface" FILE "mymetadata.json")
    Q_INTERFACES(FXInterface)

public:
    FXPlugin();
    virtual ~FXPlugin();
    virtual QString getName() const;
    virtual void apply() const override;

//public slots:
//    virtual void doSomething();
};

#endif // FXPLUGIN_H
