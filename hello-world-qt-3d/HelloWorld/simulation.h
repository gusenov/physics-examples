#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QVector3D>
#include <btBulletDynamicsCommon.h>

class Simulation : public QObject
{
    Q_OBJECT
private:
    Q_PROPERTY(QVector3D spherePosition READ spherePositionValue NOTIFY spherePositionValueChanged)
    Q_PROPERTY(qreal sphereRadius READ sphereRadiusValue CONSTANT)
    Q_PROPERTY(QVector3D groundPosition READ groundPositionValue CONSTANT)
    Q_PROPERTY(QVector3D groundHalfExtents READ groundHalfExtentsValue CONSTANT)

    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;
    btBroadphaseInterface* m_overlappingPairCache;
    btSequentialImpulseConstraintSolver* m_solver;
    btDiscreteDynamicsWorld* m_dynamicsWorld;

    // Collision shapes надо переиспользовать в rigid bodies при любой возможности!
    btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

    btDefaultMotionState* m_sphereMotionState;

    QVector3D m_spherePosition;
    qreal const m_sphereRadius;

    QVector3D const m_groundPosition;
    QVector3D const m_groundHalfExtents;

    void printPositionsOfAllObjects();

public:
    explicit Simulation(QObject *parent = nullptr);
    ~Simulation() override;

    Q_INVOKABLE void step(qreal timeStep, int maxSubSteps = 1, qreal fixedTimeStep = 1. / 60.);

    QVector3D spherePositionValue() const;
    qreal sphereRadiusValue() const;

    QVector3D groundPositionValue() const;
    QVector3D groundHalfExtentsValue() const;

signals:

    void spherePositionValueChanged(QVector3D);
};

#endif // SIMULATION_H
