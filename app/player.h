#ifndef PLAYER_H
#define PLAYER_H
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QIcon>


class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = 0);
    QPushButton *m_pauseBtn;
    QPushButton *m_playBtn;
    QPushButton *m_stopBtn;
signals:

public slots:

private:
    void createUi();
    void connectUi();

protected:
    QIcon m_playIcon;
    QIcon m_stopIcon;
    QIcon m_pauseIcon;


};

#endif // PLAYER_H
