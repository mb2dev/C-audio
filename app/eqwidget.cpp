#include "eqwidget.h"

EQWidget::EQWidget(QWidget *parent)
    : QWidget(parent)
    , m_dial(new QDial(this))
    , m_layout(new QVBoxLayout)
    , m_label(new QLabel(this))
{
    createUi();
    connectUi();
}

void EQWidget::setName(const QString name){
    m_name = name;
    m_label->setText(m_name);
}

void EQWidget::createUi()
{
    m_dial->setFixedSize(QSize(50,50));
    m_layout->addWidget(m_dial);
    m_label->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_layout->addWidget(m_label);

    this->setLayout(m_layout);
}

void EQWidget::connectUi()
{

}
