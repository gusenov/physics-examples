QT += quick \
    3dcore 3drender 3dinput 3dextras 3dquick 3dquickextras

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        myopenglfunctions.cpp \
        myquickitem.cpp \
        myquickview.cpp \
        simulation.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    myopenglfunctions.h \
    myquickitem.h \
    myquickview.h \
    simulation.h

# Bullet
macx {
    BULLET = /usr/local/Cellar/bullet/2.88_1
    LIBS += -L$${BULLET}/lib/ -lBullet2FileLoader -lBullet3Collision -lBullet3Common -lBullet3Dynamics -lBullet3Geometry -lBullet3OpenCL_clew -lBulletCollision -lBulletDynamics -lBulletFileLoader -lBulletInverseDynamics -lBulletInverseDynamicsUtils -lBulletRobotics -lBulletSoftBody -lBulletWorldImporter -lBulletXmlWorldImporter -lConvexDecomposition -lGIMPACTUtils -lHACD -lLinearMath
    INCLUDEPATH += $${BULLET}/include/bullet
}
