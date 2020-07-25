1. Создайте btDiscreteDynamicsWorld или btSoftRigidDynamicsWorld. Эти классы унаследованы от btDynamicsWorld, предоставляют высокоуровневый интерфейс, который управляет физическими объектами и constraints. Они также имплементируют обновление всех объектов на каждом фрейме.
2. Создайте btRigidBody и добавьте его в btDynamicsWorld. Для конструирования btRigidBody или btCollisionObject нужно предоставить:
   - Массу, положительную для dynamics moving objects и 0 для static объектов.
   - CollisionShape такой как Box, Sphere, Cone, Convex Hull или Triangle Mesh.
   - Свойства материала: трение (friction) и упругость (restitution).
3. Обновляйте симуляцию на каждом фрейме с помощью stepSimulation. btDiscreteDynamicsWorld автоматически учитывает variable timestep выполняя интерполяцию вместо симуляции для маленьких timestep-ов. Используется внутренний фиксированный timestep в 60 Hertz. stepSimulation будет выполнять collision detection и physics simulation. Он будет обновлять world transform для активных объектов вызывая setWorldTransform у btMotionState.
