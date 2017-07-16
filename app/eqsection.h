#ifndef EQSECTION_H
#define EQSECTION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDial>
#include <QSlider>
#include "eqwidget.h"

class EQSection : public QWidget
{
    Q_OBJECT
public:
    explicit EQSection(QWidget *parent = 0);

signals:

public slots:


protected:
    QVBoxLayout *m_layout;
    EQWidget *m_high;
    EQWidget *m_medium;
    EQWidget *m_bass;

private:
    void createUi();
    void connectUi();
};

#endif // EQSECTION_H
