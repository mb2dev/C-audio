#include "audiosection.h"

#include "../spectrum/waveform.h"
#include "../spectrum/progressbar.h"
#include "../spectrum/spectrograph.h"
#include "../spectrum/engine.h"
#include "../spectrum/levelmeter.h"
#include <QSlider>

AudioSection::AudioSection(QWidget *parent, const int orientation)
    : QWidget(parent)
    , m_progressBar(new ProgressBar(this))
    , m_fx(new FXSection(this))
    , m_eq(new EQSection(this))
    , m_volume(new QSlider(this))
    , m_spectrograph(new Spectrograph(this))
    , m_levelMeter(new LevelMeter(this))
    , m_waveform(new Waveform(this))
    , m_player(new Player(this))
    , m_orientation(orientation)
{

    createUi();
    connectUi();

}

AudioSection::~AudioSection()
{

}

void AudioSection::createUi()
{
    QGridLayout *grid = new QGridLayout;

    // http://doc.qt.io/qt-5/qscopedpointer.html#details
    QScopedPointer<QHBoxLayout> waveformLayout(new QHBoxLayout);
    waveformLayout->addWidget(m_progressBar);
    m_progressBar->setMinimumHeight(m_waveform->minimumHeight());
    waveformLayout->setMargin(0);
    m_waveform->setLayout(waveformLayout.data());
    waveformLayout.take();

    // Spectrograph and level meter

    QScopedPointer<QHBoxLayout> analysisLayout(new QHBoxLayout);
    analysisLayout->addWidget(m_spectrograph);
    analysisLayout->addWidget(m_levelMeter);

    if(m_orientation == 0){
        grid->addWidget(m_fx, 0, 0, 1, 4);
        grid->addWidget(m_eq, 1, 5, 2, 1, Qt::AlignCenter);
        grid->addWidget(m_volume, 3, 5, Qt::AlignCenter);
        grid->addWidget(m_waveform, 1, 0, 1, 5);
//        grid->addWidget(m_spectrum, 3, 0, 2, 5);
        grid->addLayout(analysisLayout.data(), 2, 0, 2, 5);
        grid->addWidget(m_player, 4, 0, 1, 2);
    }else{
        grid->addWidget(m_eq, 1, 0, 2, 1, Qt::AlignCenter);
        grid->addWidget(m_volume, 3, 0, Qt::AlignCenter);
        grid->addWidget(m_fx, 0, 1, 1, 4);
        grid->addWidget(m_waveform, 1, 1, 1, 5);
//        grid->addWidget(m_spectrum, 3, 1, 2, 5);
        grid->addLayout(analysisLayout.data(), 2, 1, 2, 5);
        grid->addWidget(m_player, 4, 1, 1, 2);
    }
    analysisLayout.take();

    this->setLayout(grid);
}

void AudioSection::connectUi()
{

}
