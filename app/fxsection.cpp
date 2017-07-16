#include "fxsection.h"
#include <QLabel>

FXSection::FXSection(QWidget *parent)
    : QWidget(parent)
    , m_param_one(new QDial(this))
    , m_param_two(new QDial(this))
    , m_param_three(new QDial(this))
    , m_combo(new QComboBox(this))
    , m_layout(new QGridLayout)
{
    createUi();
    connectUi();
}

void FXSection::createUi()
{
    m_combo->addItem("Reverb");
    m_combo->addItem("Compressor");
    m_combo->addItem("Delay");

    m_layout->addWidget(m_combo, 0, 0, 2, 1);

    m_layout->addWidget(m_param_one, 0, 1);
    QLabel *paramOne = new QLabel("Param 1");
    paramOne->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_layout->addWidget(paramOne, 1, 1);

    m_layout->addWidget(m_param_two, 0, 2);
    QLabel *paramTwo = new QLabel("Param 2");
    paramTwo->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_layout->addWidget(paramTwo, 1, 2);

    m_layout->addWidget(m_param_three, 0, 3);
    QLabel *paramThree = new QLabel("Param 3");
    paramThree->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    m_layout->addWidget(paramThree, 1, 3);

    this->setLayout(m_layout);
    this->setStyleSheet("background-color : red");
}

void FXSection::connectUi()
{

}

