#ifndef MYOPENGLFUNCTIONS_H
#define MYOPENGLFUNCTIONS_H

#include <QObject>
#include <QtGui/QOpenGLFunctions>
#include <QElapsedTimer>

class Simulation;

class MyOpenGLFunctions
    : public QObject
    , protected QOpenGLFunctions
{
    Q_OBJECT
private:
    QElapsedTimer m_elapsedTimer;
    qint64 prev_frame_tick, curr_frame_tick;
    Simulation* m_simulation;

public:
    explicit MyOpenGLFunctions(QObject *parent = nullptr);

    void setSimulationValue(Simulation*);

signals:

public slots:
    void slotBeforeRendering();
};

#endif // MYOPENGLFUNCTIONS_H
