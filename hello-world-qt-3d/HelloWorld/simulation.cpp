#include "simulation.h"

Simulation::Simulation(QObject *parent)
    : QObject(parent)
    , m_spherePosition(2, 10, 0)
    , m_sphereRadius(1.)
    , m_groundPosition(0, -56, 0)
    , m_groundHalfExtents(50., 50., 50.)
{
    // Создание dynamics world:

    // Collision configuration содержит настройки по умолчанию для памяти,
    // настройки для столкновений. Можно создавать свои конфигурации:
    m_collisionConfiguration = new btDefaultCollisionConfiguration();

    // Использование collision-диспетчера по умолчанию.
    // Для параллельной обработки можно использовать другой диспетчер.
    m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);


    // btDbvtBroadphase хороший general purpose вариант для широкой фазы
    // (broadphase). Можно также попробовать btAxis3Sweep.
    m_overlappingPairCache = new btDbvtBroadphase();

    // Широкая фаза - одна из стадий определения столкновений.
    // Изначально из всех объектов (например, физических тел) находят пары
    // потенциально пересекающихся. “Потенциально пересекающихся” - означает не
    // точную проверку на пересечение, а проверку упрощенной геометрии.
    // От выбора широкой фазы во многом может зависеть производительность
    // риложения при большом количестве тел.


    // Constraint solver по умолчанию.
    // Для параллельной обработки можно использовать другой solver.
    m_solver = new btSequentialImpulseConstraintSolver;

    // Солвер физического движка отвечает за разрешение контактов
    // и других видов связей.


    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);
    m_dynamicsWorld->setGravity(btVector3(0 , -10 , 0));

    // Создание нескольких простых rigid bodies:

    // Земля это куб со стороной 100 в позиции y = -56.
    // Сфера ударит по нему в точке y = -6, с центром в точке -5.

	{
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(m_groundHalfExtents.x()), btScalar(m_groundHalfExtents.y()), btScalar(m_groundHalfExtents.z())));
		m_collisionShapes.push_back(groundShape);

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(m_groundPosition.x(), m_groundPosition.y(), m_groundPosition.z()));

        // Rigidbody динамическое только если его масса не равна нулю, в противном случае оно статическое:
        btScalar mass(0.);
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

        // Использование motionstate опционально, оно предоставляет
        // интерполяционные возможности и синхронизирует только 'активные' объекты:
		btDefaultMotionState* groundMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, groundMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

        // Добавить тело в динамический мир:
		m_dynamicsWorld->addRigidBody(body);
	}

	{
		// Создание динамического rigidbody:

		btCollisionShape* colShape = new btSphereShape(btScalar(m_sphereRadius));
		m_collisionShapes.push_back(colShape);

		btTransform startTransform;
		startTransform.setIdentity();
        startTransform.setOrigin(btVector3(m_spherePosition.x(), m_spherePosition.y(), m_spherePosition.z()));

        // Rigidbody динамическое только если его масса не равна нулю,
        // в противном случае оно статическое:
        btScalar mass(1.f);
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

        // Использование motionstate опционально, оно предоставляет
        // интерполяционные возможности и синхронизирует только 'активные' объекты:
		m_sphereMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_sphereMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

        // Добавить тело в динамический мир:
		m_dynamicsWorld->addRigidBody(body);
	}
}

Simulation::~Simulation()
{
    // В конце программы нужно удалить все объекты в обратном созданию порядке.

    // Изъять rigidbodies из dynamics world, а затем удалить их:
    for (int i = m_dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
    {
        btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState())
            delete body->getMotionState();
        m_dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    // delete collision shapes
    for (int j = 0; j < m_collisionShapes.size(); j++)
    {
        btCollisionShape* shape = m_collisionShapes[j];
        m_collisionShapes[j] = 0;
        delete shape;
    }

    delete m_dynamicsWorld;
    delete m_solver;
    delete m_overlappingPairCache;  // delete broadphase
    delete m_dispatcher;
    delete m_collisionConfiguration;

    m_collisionShapes.clear();
}

// После того как мир создан можно пошагово запускать симуляцию:
Q_INVOKABLE void Simulation::step(qreal timeStep, int maxSubSteps, qreal fixedTimeStep)
{
    // stepSimulation proceeds the simulation over 'timeStep', units in preferably in seconds.
    // By default, Bullet will subdivide the timestep in constant substeps of each 'fixedTimeStep'.
    // in order to keep the simulation real-time, the maximum number of substeps can be clamped to 'maxSubSteps'.
    // You can disable subdividing the timestep/substepping by passing maxSubSteps=0 as second argument to stepSimulation,
    // but in that case you have to keep the timeStep constant.

    m_dynamicsWorld->stepSimulation(
        btScalar(timeStep)
        , maxSubSteps
        , btScalar(fixedTimeStep));

//    printPositionsOfAllObjects();

    {
        btTransform trans;
        m_sphereMotionState->getWorldTransform(trans);
        auto& origin = trans.getOrigin();
        m_spherePosition = QVector3D(origin.getX(), origin.getY(), origin.getZ());
        emit spherePositionValueChanged(m_spherePosition);
    }
}

// Вывод позиций всех объектов:
void Simulation::printPositionsOfAllObjects()
{
    for (int j = m_dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
    {
        btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[j];
        btRigidBody* body = btRigidBody::upcast(obj);
        btTransform trans;
        if (body && body->getMotionState())
            body->getMotionState()->getWorldTransform(trans);
        else
            trans = obj->getWorldTransform();

        printf("world pos object %d = %f, %f, %f\n"
            , j
            , float(trans.getOrigin().getX())
            , float(trans.getOrigin().getY())
            , float(trans.getOrigin().getZ())
        );
    }
}

QVector3D Simulation::spherePositionValue() const
{
    return m_spherePosition;
}

qreal Simulation::sphereRadiusValue() const
{
    return m_sphereRadius;
}

QVector3D Simulation::groundPositionValue() const
{
    return m_groundPosition;
}

QVector3D Simulation::groundHalfExtentsValue() const
{
    return m_groundHalfExtents;
}
