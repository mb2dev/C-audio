#include "player.h"
#include <QStyle>

Player::Player(QWidget *parent)
    : QWidget(parent)
    , m_playBtn(new QPushButton(this))
    , m_stopBtn(new QPushButton(this))
    , m_pauseBtn(new QPushButton(this))
{
    createUi();
    connectUi();
}

void Player::createUi()
{
    QHBoxLayout *layout = new QHBoxLayout;

    const QSize buttonSize(30, 30);

    m_pauseIcon = style()->standardIcon(QStyle::SP_MediaPause);
    m_pauseBtn->setIcon(m_pauseIcon);
    m_pauseBtn->setEnabled(false);
    m_pauseBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_pauseBtn->setMinimumSize(buttonSize);

    m_playIcon = style()->standardIcon(QStyle::SP_MediaPlay);
    m_playBtn->setIcon(m_playIcon);
    m_playBtn->setEnabled(false);
    m_playBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_playBtn->setMinimumSize(buttonSize);

    m_stopIcon = style()->standardIcon(QStyle::SP_MediaStop);
    m_stopBtn->setIcon(m_stopIcon);
    m_stopBtn->setEnabled(false);
    m_stopBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_stopBtn->setMinimumSize(buttonSize);

    layout->addWidget(m_playBtn);
    layout->addWidget(m_pauseBtn);
    layout->addWidget(m_stopBtn);

    this->setLayout(layout);
}

void Player::connectUi()
{

}
