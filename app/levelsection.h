#ifndef LEVELSECTION_H
#define LEVELSECTION_H

#include <QSlider>
#include <QWidget>

class LevelSection : public QWidget
{
    Q_OBJECT
public:
    explicit LevelSection(QWidget *parent = 0);

signals:

public slots:

protected:
    QSlider *m_slider;

private:
    void createUi();
    void connectUi();
};

#endif // LEVELSECTION_H
