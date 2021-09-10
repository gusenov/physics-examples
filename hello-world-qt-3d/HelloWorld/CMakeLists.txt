cmake_minimum_required(VERSION 3.14)

project(HelloWorld LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        myquickview.cpp
        myquickitem.cpp
        myopenglfunctions.cpp
        simulation.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HelloWorld
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(HelloWorld SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(HelloWorld
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(HelloWorld
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(HelloWorld
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)




# Bullet
target_include_directories(${PROJECT_NAME} PRIVATE "/usr/local/include/bullet/")
target_link_directories(${PROJECT_NAME} PRIVATE "/usr/local/lib/")
target_link_libraries(${PROJECT_NAME} PRIVATE
	Bullet2FileLoader
	Bullet3Collision
	Bullet3Common
	Bullet3Dynamics
	Bullet3Geometry
	Bullet3OpenCL_clew
	BulletCollision
	BulletDynamics
	BulletFileLoader
	BulletInverseDynamics
	BulletInverseDynamicsUtils
	BulletRobotics
	BulletSoftBody
	BulletWorldImporter
	BulletXmlWorldImporter
	ConvexDecomposition
	GIMPACTUtils
	HACD
	LinearMath)
