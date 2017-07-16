#include "audiosection.h"

#include "soundmanager.h"
#include "soundplayer.h"

#include "../spectrum/waveform.h"
#include "../spectrum/progressbar.h"
#include "../spectrum/spectrograph.h"
#include "../spectrum/engine.h"
#include "../spectrum/levelmeter.h"
#include "../spectrum/spectrum.h"
#include <QSlider>
#include <QMessageBox>
#include <QTimerEvent>

const int NullTimerId = -1;

AudioSection::AudioSection(QWidget *parent, const int orientation, SoundManager* soundmanager)
    : QWidget(parent)
    , m_engine(new Engine(this))
    , m_progressBar(new ProgressBar(this))
    , m_fx(new FXSection(this))
    , m_eq(new EQSection(this))
    , m_volume(new QSlider(this))
    , m_spectrograph(new Spectrograph(this))
    , m_levelMeter(new LevelMeter(this))
    , m_waveform(new Waveform(this))
    , m_player(new Player(this))
    , m_orientation(orientation)
    , m_infoMessage(new QLabel(tr("Select a mode to begin")/*, this*/))
    , m_infoMessageTimerId(NullTimerId)
    , m_soundmanager(soundmanager)
{
    m_spectrograph->setParams(SpectrumNumBands, SpectrumLowFreq, SpectrumHighFreq);
    createUi();
    connectUi();

}

AudioSection::~AudioSection()
{

}

void AudioSection::createUi()
{
    m_volume->setMaximum(100);
    m_volume->setMinimum(0);
    m_volume->setSliderPosition(100);

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

    connect(m_volume, SIGNAL(valueChanged(int)), this, SLOT(updateVolume(int)));
    connect(m_eq->m_high->m_dial, SIGNAL(valueChanged(int)), this, SLOT(updateHighFilter(int)));
    connect(m_eq->m_medium->m_dial, SIGNAL(valueChanged(int)), this, SLOT(updateMediumFilter(int)));
    connect(m_eq->m_bass->m_dial, SIGNAL(valueChanged(int)), this, SLOT(updateLowFilter(int)));

    ///////////////////////////////////////////////////////////

    connect(m_player->m_pauseBtn, SIGNAL(clicked()), m_engine, SLOT(suspend()));

    connect(m_player->m_playBtn, SIGNAL(clicked()),
            m_engine, SLOT(startPlayback()));

    connect(m_player->m_pauseBtn, SIGNAL(clicked()), this, SLOT(suspend()));

    connect(m_player->m_playBtn, SIGNAL(clicked()),
            this, SLOT(startPlayback()));

    ////////////////////////////////////////////////////////////

    connect(m_engine, SIGNAL(stateChanged(QAudio::Mode,QAudio::State)),
            this, SLOT(stateChanged(QAudio::Mode,QAudio::State)));

    connect(m_engine, SIGNAL(formatChanged(const QAudioFormat &)),
            this, SLOT(formatChanged(const QAudioFormat &)));

    m_progressBar->bufferLengthChanged(m_engine->bufferLength());

    connect(m_engine, SIGNAL(bufferLengthChanged(qint64)),
            this, SLOT(bufferLengthChanged(qint64)));

    connect(m_engine, SIGNAL(dataLengthChanged(qint64)),
            this, SLOT(updateButtonStates()));

    connect(m_engine, SIGNAL(recordPositionChanged(qint64)),
            m_progressBar, SLOT(recordPositionChanged(qint64)));

    connect(m_engine, SIGNAL(playPositionChanged(qint64)),
            m_progressBar, SLOT(playPositionChanged(qint64)));

    connect(m_engine, SIGNAL(recordPositionChanged(qint64)),
            this, SLOT(audioPositionChanged(qint64)));

    connect(m_engine, SIGNAL(playPositionChanged(qint64)),
            this, SLOT(audioPositionChanged(qint64)));

    connect(m_engine, SIGNAL(levelChanged(qreal, qreal, int)),
            m_levelMeter, SLOT(levelChanged(qreal, qreal, int)));

    connect(m_engine, SIGNAL(spectrumChanged(qint64, qint64, const FrequencySpectrum &)),
            this, SLOT(spectrumChanged(qint64, qint64, const FrequencySpectrum &)));

    connect(m_engine, SIGNAL(infoMessage(QString, int)),
            this, SLOT(infoMessage(QString, int)));

    connect(m_engine, SIGNAL(errorMessage(QString, QString)),
            this, SLOT(errorMessage(QString, QString)));

    connect(m_spectrograph, SIGNAL(infoMessage(QString, int)),
            this, SLOT(infoMessage(QString, int)));

    connect(m_engine, SIGNAL(bufferChanged(qint64, qint64, const QByteArray &)),
            m_waveform, SLOT(bufferChanged(qint64, qint64, const QByteArray &)));
}

void AudioSection::updateButtonStates()
{
//    const bool recordEnabled = ((QAudio::AudioOutput == m_engine->mode() ||
//                                (QAudio::ActiveState != m_engine->state() &&
//                                 QAudio::IdleState != m_engine->state())) &&
//                                RecordMode == m_mode);
//    m_recordButton->setEnabled(recordEnabled);

    const bool pauseEnabled = (QAudio::ActiveState == m_engine->state() ||
                               QAudio::IdleState == m_engine->state());
    m_player->m_pauseBtn->setEnabled(pauseEnabled);

    const bool playEnabled = (/*m_engine->dataLength() &&*/
                              (QAudio::AudioOutput != m_engine->mode() ||
                               (QAudio::ActiveState != m_engine->state() &&
                                QAudio::IdleState != m_engine->state())));
    m_player->m_playBtn->setEnabled(playEnabled);
}

void AudioSection::reset()
{
    m_waveform->reset();
    m_engine->reset();
    m_levelMeter->reset();
    m_spectrograph->reset();
    m_progressBar->reset();
}

//-----------------------------------------------------------------------------
// Public slots
//-----------------------------------------------------------------------------

void AudioSection::updateHighFilter(int sliderValue){
    qDebug("updateHighFilter");

    float v = ((float)sliderValue)/100.0f * 90.0f - 80.0f;
    if(m_orientation == 0)
        m_soundmanager->player_a->filter(FMOD_DSP_THREE_EQ_HIGHGAIN, v);
    else
        m_soundmanager->player_b->filter(FMOD_DSP_THREE_EQ_HIGHGAIN, v);
}

void AudioSection::updateMediumFilter(int sliderValue){
    float v = ((float)sliderValue)/100.0f * 90.0f - 80.0f;
    qDebug("updateMediumFilter %.2f", v);
    if(m_orientation == 0)
        m_soundmanager->player_a->filter(FMOD_DSP_THREE_EQ_MIDGAIN, v);
    else
        m_soundmanager->player_b->filter(FMOD_DSP_THREE_EQ_MIDGAIN, v);
}

void AudioSection::updateLowFilter(int sliderValue){
    float v = ((float)sliderValue)/100.0f * 90.0f - 80.0f;
    qDebug("updateLowFilter %.2f", v);
    if(m_orientation == 0)
        m_soundmanager->player_a->filter(FMOD_DSP_THREE_EQ_LOWGAIN, v);
    else
        m_soundmanager->player_b->filter(FMOD_DSP_THREE_EQ_LOWGAIN, v);
}

void AudioSection::updateVolume(int sliderValue){
    float v = ((float)sliderValue)/(float)(m_volume->maximum());
    if(m_orientation == 0)
        m_soundmanager->player_a->setVolume(v);
    else
        m_soundmanager->player_b->setVolume(v);
}

void AudioSection::startPlayback(){
    if(m_orientation == 0)
        m_soundmanager->player_a->play();
    else
        m_soundmanager->player_b->play();
}

void AudioSection::suspend(){
    if(m_orientation == 0)
        m_soundmanager->player_a->stop();
    else
        m_soundmanager->player_b->stop();
}

void AudioSection::stateChanged(QAudio::Mode mode, QAudio::State state)
{
    Q_UNUSED(mode);

    updateButtonStates();

    if (QAudio::ActiveState != state && QAudio::SuspendedState != state) {
        m_levelMeter->reset();
        m_spectrograph->reset();
    }
}

void AudioSection::formatChanged(const QAudioFormat &format)
{
   infoMessage(formatToString(format), NullMessageTimeout);

#ifndef DISABLE_WAVEFORM
    if (QAudioFormat() != format) {
        m_waveform->initialize(format, WaveformTileLength,
                               WaveformWindowDuration);
    }
#endif
}

void AudioSection::infoMessage(const QString &message, int timeoutMs)
{
    m_infoMessage->setText(message);

    if (NullTimerId != m_infoMessageTimerId) {
        killTimer(m_infoMessageTimerId);
        m_infoMessageTimerId = NullTimerId;
    }

    if (NullMessageTimeout != timeoutMs)
        m_infoMessageTimerId = startTimer(timeoutMs);
}

void AudioSection::errorMessage(const QString &heading, const QString &detail)
{
    QMessageBox::warning(this, heading, detail, QMessageBox::Close);
}

void AudioSection::timerEvent(QTimerEvent *event)
{
    Q_ASSERT(event->timerId() == m_infoMessageTimerId);
    Q_UNUSED(event) // suppress warnings in release builds
    killTimer(m_infoMessageTimerId);
    m_infoMessageTimerId = NullTimerId;
    m_infoMessage->setText("");
}

void AudioSection::audioPositionChanged(qint64 position)
{
#ifndef DISABLE_WAVEFORM
    m_waveform->audioPositionChanged(position);
#else
    Q_UNUSED(position)
#endif
}

void AudioSection::bufferLengthChanged(qint64 length)
{
    m_progressBar->bufferLengthChanged(length);
}

void AudioSection::loadFile(int index, QString filePath){
    if(index == m_orientation){
        reset();
        m_engine->loadFile(filePath);
    }
}

void AudioSection::spectrumChanged(qint64 position, qint64 length,
                                 const FrequencySpectrum &spectrum)
{
    m_progressBar->windowChanged(position, length);
    m_spectrograph->spectrumChanged(spectrum);
}

//-----------------------------------------------------------------------------
// Private slots
//-----------------------------------------------------------------------------





