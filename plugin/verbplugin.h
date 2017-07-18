#ifndef VERBPLUGIN_H
#define VERBPLUGIN_H

#include <QObject>
#include "fxinterface.h"

class VerbPlugin : public QObject, public FXInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.gabrievv.esgi.cpp.FXInterface")
    Q_INTERFACES(FXInterface)

public:
    explicit VerbPlugin(QObject *parent = 0);
    virtual ~VerbPlugin();
    virtual QString getName() const;
    virtual void apply() const override;
signals:

public slots:
};

#endif // VERBPLUGIN_H
