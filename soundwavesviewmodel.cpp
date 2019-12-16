#include "soundwavesviewmodel.h"



WaveData::WaveData(QObject* parent):
    QObject(parent)
{

}

int WaveData::height() const
{
    return m_height;
}

void WaveData::setHeight(int height)
{
    if(m_height != height){
        m_height = height;
        heightChanged();
    }
}

SoundWavesViewModel::SoundWavesViewModel(QObject* parent) :
    QObject(parent),
    m_timerUpdate(66),
    m_wavesCount(17),
    m_upperBound(80),
    m_lowerBound(10),
    m_amplitudeModifier(1)
{
    for(auto i = 0; i < m_wavesCount; i++){
        auto waveData = new WaveData(this);
        waveData->setHeight(m_upperBound);
        m_waves.append(waveData);
    }

    m_wavesProperty = QQmlListProperty<WaveData>(this, 0, &SoundWavesViewModel::wavesCount, &SoundWavesViewModel::wave);
    start();
}

int SoundWavesViewModel::wavesCount(QQmlListProperty<WaveData> *property)
{
    SoundWavesViewModel* viewModel = qobject_cast<SoundWavesViewModel*>(property->object);
    return viewModel->m_waves.size();
}

WaveData *SoundWavesViewModel::wave(QQmlListProperty<WaveData> *property, int index)
{
    SoundWavesViewModel* viewModel = qobject_cast<SoundWavesViewModel*>(property->object);
    return viewModel->m_waves.at(index);
}

void SoundWavesViewModel::start()
{
    connect(&m_updateTimer, &QTimer::timeout, this, QOverload<>::of(&SoundWavesViewModel::_update));
    m_updateTimer.start(m_timerUpdate);
}

void SoundWavesViewModel::increaseAmplitude()
{
    m_amplitudeModifier = 3;
}

void SoundWavesViewModel::decreaseAmplitude()
{
    m_amplitudeModifier = 1;
}

void SoundWavesViewModel::_update()
{
    for(auto i = 0; i < m_wavesCount; i++){
        auto height = m_randomGenerator.bounded(m_lowerBound, m_upperBound) * m_amplitudeModifier;
        m_waves[i]->setHeight((int)height);
    }
    wavesChanged();
}

QQmlListProperty<WaveData> SoundWavesViewModel::wavesProperty() const
{
    return m_wavesProperty;
}

QList<WaveData*> SoundWavesViewModel::waves() const
{
    return m_waves;
}
