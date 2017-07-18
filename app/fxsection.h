#ifndef FXSECTION_H
#define FXSECTION_H

#include <QWidget>
#include <QDial>
#include <QHBoxLayout>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include "fxinterface.h"

class FXSection : public QWidget
{
    Q_OBJECT
public:
    explicit FXSection(QString appPath, QWidget *parent = 0);

signals:
    void valueChanged(int paramIndex, int paramType, int paramValue);
    void fxSelected(FXInterface*);
public slots:
    void paramOneChanged(int sliderValue);
    void paramTwoChanged(int sliderValue);
    void paramThreeChanged(int sliderValue);

protected:
    QString m_appPath;
    QGridLayout *m_layout;
    QComboBox *m_combo;
    QDial *m_param_one;
    QDial * m_param_two;
    QDial * m_param_three;
    FXInterface *fxInterface = nullptr;
    QLabel *m_paramOne;
    QLabel *m_paramTwo;
    QLabel *m_paramThree;

private:
    void createUi();
    void connectUi();
    bool loadPlugin();
};

#endif // FXSECTION_H
