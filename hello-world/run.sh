#!/usr/bin/env bash

EXE_FILE="./a.out"

BULLET_INC_DIR="/usr/local/include/bullet/"
BULLET_LIB_DIR="/usr/local/lib/"

BULLET_LIBS="-lBullet2FileLoader -lBullet3Collision -lBullet3Common -lBullet3Dynamics -lBullet3Geometry -lBullet3OpenCL_clew -lBulletCollision -lBulletDynamics -lBulletFileLoader -lBulletInverseDynamics -lBulletInverseDynamicsUtils -lBulletRobotics -lBulletSoftBody -lBulletWorldImporter -lBulletXmlWorldImporter -lConvexDecomposition -lGIMPACTUtils -lHACD -lLinearMath"

clang++ --std=c++17 \
    -I"$BULLET_INC_DIR" \
    -L"$BULLET_LIB_DIR" $BULLET_LIBS \
    `find . -maxdepth 1 -name "*.cc" | tr '\n' ' '` -o "$EXE_FILE" \
&& "$EXE_FILE"




# $ ls -1 /usr/local/Cellar/bullet/2.88_1/lib/*.dylib 
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet2FileLoader.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet2FileLoader.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet3Collision.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet3Collision.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet3Common.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet3Common.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet3Dynamics.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet3Dynamics.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet3Geometry.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet3Geometry.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet3OpenCL_clew.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBullet3OpenCL_clew.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletCollision.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletCollision.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletDynamics.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletDynamics.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletFileLoader.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletFileLoader.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletInverseDynamics.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletInverseDynamics.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletInverseDynamicsUtils.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletInverseDynamicsUtils.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletRobotics.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletRobotics.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletSoftBody.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletSoftBody.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletWorldImporter.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletWorldImporter.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletXmlWorldImporter.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libBulletXmlWorldImporter.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libConvexDecomposition.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libConvexDecomposition.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libGIMPACTUtils.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libGIMPACTUtils.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libHACD.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libHACD.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libLinearMath.2.88.dylib
# /usr/local/Cellar/bullet/2.88_1/lib/libLinearMath.dylib




# $ ls /usr/local/lib/libBullet*.dylib
# /usr/local/lib/libBullet2FileLoader.2.88.dylib
# /usr/local/lib/libBullet2FileLoader.dylib
# /usr/local/lib/libBullet3Collision.2.88.dylib
# /usr/local/lib/libBullet3Collision.dylib
# /usr/local/lib/libBullet3Common.2.88.dylib
# /usr/local/lib/libBullet3Common.dylib
# /usr/local/lib/libBullet3Dynamics.2.88.dylib
# /usr/local/lib/libBullet3Dynamics.dylib
# /usr/local/lib/libBullet3Geometry.2.88.dylib
# /usr/local/lib/libBullet3Geometry.dylib
# /usr/local/lib/libBullet3OpenCL_clew.2.88.dylib
# /usr/local/lib/libBullet3OpenCL_clew.dylib
# /usr/local/lib/libBulletCollision.2.88.dylib
# /usr/local/lib/libBulletCollision.dylib
# /usr/local/lib/libBulletDynamics.2.88.dylib
# /usr/local/lib/libBulletDynamics.dylib
# /usr/local/lib/libBulletFileLoader.2.88.dylib
# /usr/local/lib/libBulletFileLoader.dylib
# /usr/local/lib/libBulletInverseDynamics.2.88.dylib
# /usr/local/lib/libBulletInverseDynamics.dylib
# /usr/local/lib/libBulletInverseDynamicsUtils.2.88.dylib
# /usr/local/lib/libBulletInverseDynamicsUtils.dylib
# /usr/local/lib/libBulletRobotics.2.88.dylib
# /usr/local/lib/libBulletRobotics.dylib
# /usr/local/lib/libBulletSoftBody.2.88.dylib
# /usr/local/lib/libBulletSoftBody.dylib
# /usr/local/lib/libBulletWorldImporter.2.88.dylib
# /usr/local/lib/libBulletWorldImporter.dylib
# /usr/local/lib/libBulletXmlWorldImporter.2.88.dylib
# /usr/local/lib/libBulletXmlWorldImporter.dylib