#include "btBulletDynamicsCommon.h"
#include <cstdio>

// Демонстрация базовой Bullet physics симуляции.

int main(int argc, char** argv)
{
    int i;

    // Создание dynamics world:

    // Collision configuration содержит настройки по умолчанию для памяти,
    // настройки для столкновений. Можно создавать свои конфигурации:
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

    // Использование collision-диспетчера по умолчанию.
    // Для параллельной обработки можно использовать другой диспетчер.
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);


    // btDbvtBroadphase хороший general purpose вариант для широкой фазы
    // (broadphase). Можно также попробовать btAxis3Sweep.
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

    // Широкая фаза - одна из стадий определения столкновений.
    // Изначально из всех объектов (например, физических тел) находят пары
    // потенциально пересекающихся. “Потенциально пересекающихся” - означает не
    // точную проверку на пересечение, а проверку упрощенной геометрии.
    // От выбора широкой фазы во многом может зависеть производительность
    // риложения при большом количестве тел.


    // Constraint solver по умолчанию.
    // Для параллельной обработки можно использовать другой solver.
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    // Солвер физического движка отвечает за разрешение контактов
    // и других видов связей.


    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(
        dispatcher
        , overlappingPairCache
        , solver
        , collisionConfiguration
    );
    dynamicsWorld->setGravity(btVector3(0 , -10 ,0));

    // Collision shapes надо переиспользовать в rigid bodies при
    // любой возможности!
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    // Создание нескольких простых rigid bodies:

    // Земля это куб со стороной 100 в позиции y = -56.
	  // Сфера ударит по нему в точке y = -6, с центром в точке -5.

	{
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
		collisionShapes.push_back(groundShape);

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -56, 0));

    // Rigidbody динамическое только если его масса не равна нулю,
    // в противном случае оно статическое:
    btScalar mass(0.);
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

		// Использование motionstate опционально, оно предоставляет
    // интерполяционные возможности и синхронизирует только
    // 'активные' объекты:
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

        // Добавить тело в динамический мир:
		dynamicsWorld->addRigidBody(body);
	}

	{
		// Создание динамического rigidbody:

		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		collisionShapes.push_back(colShape);

		btTransform startTransform;
		startTransform.setIdentity();
        startTransform.setOrigin(btVector3(2, 10, 0));

    // Rigidbody динамическое только если его масса не равна нулю,
    // в противном случае оно статическое:
    btScalar mass(1.f);
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

    // Использование motionstate опционально, оно предоставляет
    // интерполяционные возможности и синхронизирует только
    // 'активные' объекты:
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

    // Добавить тело в динамический мир:
		dynamicsWorld->addRigidBody(body);
	}

    // После того как мир создан можно пошагово запускать симуляцию:
    for(i = 0; i < 150; i++) {
        dynamicsWorld->stepSimulation(1.f / 60.f, 10);

        // Вывод позиций всех объектов:
        for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
            btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
            btRigidBody* body = btRigidBody::upcast(obj);
            btTransform trans;
            if (body && body->getMotionState()) {
                body->getMotionState()->getWorldTransform(trans);
            } else {
                trans = obj->getWorldTransform();
            }
            printf("world pos object %d = %f, %f, %f\n"
                , j
                , float(trans.getOrigin().getX())
                , float(trans.getOrigin().getY())
                , float(trans.getOrigin().getZ())
            );
        }
    }

    // В конце программы нужно удалить все объекты в обратном созданию порядке.

    // Изъять rigidbodies из dynamics world, а затем удалить их:
    for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState())
            delete body->getMotionState();
        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    // delete collision shapes
    for (int j = 0; j < collisionShapes.size(); j++) {
        btCollisionShape* shape = collisionShapes[j];
        collisionShapes[j] = 0;
        delete shape;
    }

    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;  // delete broadphase
    delete dispatcher;
    delete collisionConfiguration;

    collisionShapes.clear();
}
