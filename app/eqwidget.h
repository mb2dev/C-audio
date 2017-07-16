#ifndef EQWIDGET_H
#define EQWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDial>
#include <QString>

class EQWidget : public QWidget
{

    Q_OBJECT
public:
    explicit EQWidget(QWidget *parent = 0);
    void setName(const QString);
signals:

public slots:

protected:
    QDial *m_dial;
    QLabel *m_label;
    QVBoxLayout *m_layout;
private:
    QString m_name;

private:
    void createUi();
    void connectUi();
};

#endif // EQWIDGET_H
