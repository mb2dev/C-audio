#ifndef FXSECTION_H
#define FXSECTION_H

#include <QWidget>
#include <QDial>
#include <QHBoxLayout>
#include <QComboBox>
#include <QGridLayout>

class FXSection : public QWidget
{
    Q_OBJECT
public:
    explicit FXSection(QWidget *parent = 0);

signals:

public slots:

protected:
    QGridLayout *m_layout;
    QComboBox *m_combo;
    QDial *m_param_one;
    QDial * m_param_two;
    QDial * m_param_three;

private:
    void createUi();
    void connectUi();
};

#endif // FXSECTION_H
