#include "myquickitem.h"
#include <QtQuick/qquickwindow.h>

MyQuickItem::MyQuickItem()
    : m_myOpenGLFunctions(nullptr)
{
    connect(this, &QQuickItem::windowChanged, this, &MyQuickItem::slotWindowChanged);
}

MyQuickItem::~MyQuickItem()
{
    delete m_myOpenGLFunctions;
}

Simulation* MyQuickItem::simulationValue() const
{
    return m_simulation;
}

void MyQuickItem::setSimulationValue(Simulation* simulation)
{
    m_simulation = simulation;
    emit simulationValueChanged(m_simulation);
}

void MyQuickItem::slotWindowChanged(QQuickWindow* win)
{
    if (win)
    {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &MyQuickItem::slotBeforeSynchronizing, Qt::DirectConnection);
    }
}

void MyQuickItem::slotBeforeSynchronizing()
{
    auto win = window();
    if (!win)
        return;

    if (!m_myOpenGLFunctions)
    {
        m_myOpenGLFunctions = new MyOpenGLFunctions();
        m_myOpenGLFunctions->setSimulationValue(m_simulation);
        connect(win, &QQuickWindow::beforeRendering, m_myOpenGLFunctions, &MyOpenGLFunctions::slotBeforeRendering, Qt::DirectConnection);
    }
}
