#ifndef FXINTERFACE_H
#define FXINTERFACE_H
#include <QtPlugin>

class QString;

class FXInterface {

public:
    virtual ~FXInterface(){}
    virtual void apply() const = 0;
    virtual QString getName() const = 0;

protected:
    QString m_Name;

private:
    void createUi();
    void connectUi();
};

#define FXInterface_iid "com.gabrievv.esgi.cpp.FXInterface"

Q_DECLARE_INTERFACE(FXInterface, FXInterface_iid)

#endif // FXINTERFACE_H
