#ifndef SOUNDWAVESVIEWMODEL_H
#define SOUNDWAVESVIEWMODEL_H

#include <QObject>
#include <QTimer>

#include <QRandomGenerator>
#include <QQmlListProperty>

class WaveData : public QObject
{
    Q_OBJECT

public:
    WaveData(QObject* parent = nullptr);

    Q_PROPERTY(int height
               READ height
               NOTIFY heightChanged)

    int height() const;
    void setHeight(int height);

signals:
    void heightChanged();

private:
    int m_height;
};



class SoundWavesViewModel : public QObject
{
    Q_OBJECT
public:
    SoundWavesViewModel(QObject* parent = nullptr);

    Q_PROPERTY(QQmlListProperty<WaveData>       waves
        READ                                    wavesProperty
        NOTIFY                                  wavesChanged)

public:
    Q_INVOKABLE void start();
    Q_INVOKABLE void increaseAmplitude();
    Q_INVOKABLE void decreaseAmplitude();

    QQmlListProperty<WaveData> wavesProperty() const;
    QList<WaveData*> waves() const;
    void setWaves(const QList<int> &waves);

    static int wavesCount(QQmlListProperty<WaveData>* property);
    static WaveData* wave(QQmlListProperty<WaveData>* property, int index);


private:
    void _update();

private:
    QQmlListProperty<WaveData> m_wavesProperty;
    QList<WaveData*> m_waves;
    QTimer m_updateTimer;
    QRandomGenerator m_randomGenerator;
    int m_timerUpdate;
    int m_wavesCount;
    int m_upperBound;
    int m_lowerBound;
    float m_amplitudeModifier;

signals:
    void wavesChanged();
};

#endif // SOUNDWAVESVIEWMODEL_H
