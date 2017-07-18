#include "eqsection.h"
#include <QLabel>

EQSection::EQSection(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout)
    , m_high(new EQWidget(this))
    , m_medium(new EQWidget(this))
    , m_bass(new EQWidget(this))
{
    createUi();
    connectUi();
}

void EQSection::createUi()
{
    m_high->setName("High");
    m_medium->setName("Medium");
    m_bass->setName("Low");

    this->setStyleSheet("QDial { background-color: blue }");

    m_layout->addWidget(m_high);
    m_layout->addWidget(m_medium);
    m_layout->addWidget(m_bass);

    this->setLayout(m_layout);
}

void EQSection::connectUi()
{

}
