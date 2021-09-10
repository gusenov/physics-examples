#ifndef MYQUICKITEM_H
#define MYQUICKITEM_H

#include <QQuickItem>
#include "myopenglfunctions.h"

class Simulation;

class MyQuickItem : public QQuickItem
{
    Q_OBJECT
private:
    Q_PROPERTY(Simulation* simulation WRITE setSimulationValue READ simulationValue NOTIFY simulationValueChanged)

    MyOpenGLFunctions* m_myOpenGLFunctions;
    Simulation* m_simulation;

public:
    MyQuickItem();
    ~MyQuickItem() override;

    Simulation* simulationValue() const;
    void setSimulationValue(Simulation*);

signals:

    void simulationValueChanged(Simulation*);

public slots:
    void slotWindowChanged(QQuickWindow* win);
    void slotBeforeSynchronizing();
};

#endif // MYQUICKITEM_H
