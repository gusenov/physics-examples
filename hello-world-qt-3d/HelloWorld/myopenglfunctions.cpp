#include "myopenglfunctions.h"
#include "simulation.h"
#include <QThread>

MyOpenGLFunctions::MyOpenGLFunctions(QObject *parent)
    : QObject(parent)
    , m_simulation(nullptr)
    , prev_frame_tick(0)
{
    m_elapsedTimer.start();
    curr_frame_tick = m_elapsedTimer.elapsed();
}

void MyOpenGLFunctions::setSimulationValue(Simulation* simulation)
{
    m_simulation = simulation;
}

void MyOpenGLFunctions::slotBeforeRendering()
{
    prev_frame_tick = curr_frame_tick;
    curr_frame_tick = m_elapsedTimer.elapsed();
    m_simulation->step(curr_frame_tick - prev_frame_tick, 10);
    QThread::msleep(16);
}
