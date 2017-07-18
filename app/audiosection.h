#ifndef AUDIOSECTION_H
#define AUDIOSECTION_H

#include <QGridLayout>
#include <QWidget>
#include <QAudio>

#include "fxinterface.h"
#include "fxsection.h"
#include "eqsection.h"
#include "levelsection.h"
#include "player.h"
#include "soundmanager.h"

class Waveform;
class ProgressBar;
class Spectrograph;
class LevelMeter;
class FrequencySpectrum;
class Engine;
class QSlider;

QT_BEGIN_NAMESPACE
class QAudioFormat;
QT_END_NAMESPACE

class AudioSection : public QWidget
{
    Q_OBJECT
public:
    explicit AudioSection(QWidget *parent = 0, const int orientation = 0, SoundManager* soundmanager = nullptr, QString appPath = "");
    ~AudioSection();

    // QObject
    void timerEvent(QTimerEvent *event) override;

    SoundManager* m_soundmanager;

signals:

public slots:
    void fxChanged(FXInterface*);
    void fxParamValueChanged(int, int, int);
    void loadFile(int index, QString filePath);
    void stateChanged(QAudio::Mode mode, QAudio::State state);
    void formatChanged(const QAudioFormat &format);
    void spectrumChanged(qint64 position, qint64 length,
                         const FrequencySpectrum &spectrum);
    void infoMessage(const QString &message, int timeoutMs);
    void errorMessage(const QString &heading, const QString &detail);
    void audioPositionChanged(qint64 position);
    void bufferLengthChanged(qint64 length);
    void startPlayback();
    void suspend();
    void updateVolume(int);
    void updateHighFilter(int);
    void updateMediumFilter(int);
    void updateLowFilter(int);

private slots:
    void updateButtonStates();

protected:
    QWidget *m_spectrum;
    Waveform *m_waveform;
    EQSection *m_eq;
    FXSection *m_fx;
    QSlider *m_volume;
    Player * m_player;
    int m_orientation;
    QLabel* m_infoMessage;
    int m_infoMessageTimerId;

private:
    void reset();
    void createUi();
    void connectUi();
    Engine*                 m_engine;
    ProgressBar*            m_progressBar;
    Spectrograph*           m_spectrograph;
    LevelMeter*             m_levelMeter;
};

#endif // AUDIOSECTION_H
