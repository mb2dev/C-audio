#ifndef AUDIOSECTION_H
#define AUDIOSECTION_H

#include <QGridLayout>
#include <QWidget>
#include "fxsection.h"
#include "eqsection.h"
#include "levelsection.h"
#include "player.h"

class Waveform;
class ProgressBar;
class Spectrograph;
class LevelMeter;
class FrequencySpectrum;
class Engine;
class QSlider;

class AudioSection : public QWidget
{
    Q_OBJECT
public:
    explicit AudioSection(QWidget *parent = 0, const int orientation = 0);
    ~AudioSection();

signals:

public slots:

protected:
    QWidget *m_spectrum;
    Waveform *m_waveform;
    EQSection *m_eq;
    FXSection *m_fx;
    QSlider *m_volume;
    Player * m_player;
    int m_orientation;

private:
    void createUi();
    void connectUi();
    Engine*                 m_engine;
    ProgressBar*            m_progressBar;
    Spectrograph*           m_spectrograph;
    LevelMeter*             m_levelMeter;
};

#endif // AUDIOSECTION_H
