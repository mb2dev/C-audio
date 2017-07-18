#ifndef ECHOPLUGIN_H
#define ECHOPLUGIN_H

#include <QObject>
#include "fxinterface.h"

class EchoPlugin : public QObject, public FXInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.gabrievv.esgi.cpp.FXInterface")
    Q_INTERFACES(FXInterface)

public:
    explicit EchoPlugin(QObject *parent = 0);
    virtual ~EchoPlugin();
    virtual QString getName() const;
    virtual void apply() const override;
signals:

public slots:
};

#endif // ECHOPLUGIN_H
