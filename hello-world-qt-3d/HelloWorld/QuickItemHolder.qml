import QtQuick 2.0
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import QtQuick.Scene3D 2.0

import com.example.MyQuickItem 1.0
import com.example.Simulation 1.0

Item {
    rotation: 0
    transformOrigin: Item.Center
    clip: false

    MyQuickItem {
        clip: true
        z: 0

        anchors.fill: parent

        simulation: Simulation {
            id: mySimulation
        }

        Timer {
            property int i: 0
            property real timeStep: 1.0 / 60.0  // seconds

            interval: timeStep * 1000  // milliseconds
            running: false
            repeat: i < 150
            onTriggered: {
                mySimulation.step(timeStep, 10)
                ++i
            }
        }

        Scene3D {  // элемент трехмерной сцены

            anchors.fill: parent  // делаем так, чтобы он заполнил всю его область

            focus: true  // для того чтобы сцена гарантированно получала ввод пользователя

            // а для того чтобы сцена могла его интерпретировать,
            // присваиваем свойству aspects массив из двух значений: "input" и "logic"
            aspects: ["input", "logic"]

            // не хотим,
            // чтобы в случае изменения размеров окна при отображении происходило искажение
            // объектов сцены
            cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

            Entity {  // элемент сущности, который объединяет в себе все элементы трехмерной сцены:

                Camera {  // Камера
                    id: camera
                    nearPlane : 0.1  // значения ближнего
                    farPlane : 1000.0  // и дальнего фокусных расстояний
                    position: Qt.vector3d(0.0, 0.0, 250.0)  // помещаем камеру на 50 единиц от начала положения координат вдоль оси Z
                }

                FirstPersonCameraController {  // Управление положением камеры
                    // уникальный идентификатор нашей камеры, чтобы дать возможность пользователям
                    // управлять созданной камерой при помощи мыши, курсоров, тачпада, сенсорного экрана и т. п.;
                    camera: camera

                    linearSpeed: 1000.0
                    acceleration: 0.1
                    deceleration: 1.0
                }

                components: [  // объединяет в сущности сцены настройки рендеринга с пользовательским вводом
                    RenderSettings {  // Рендеринг - это процесс создания двумерного изображения из трехмерной сцены.
                        activeFrameGraph:
                            ForwardRenderer {
                                camera: camera  // Для осуществления рендеринга необходима камера

                                // Для того чтобы был виден черный цвет фона главного элемента окна Rectange, мы делаем цвет очистки прозрачным
                                clearColor: "transparent"
                            }
                    },
                    InputSettings { }
                ]

                // задает направленный источник света
                DirectionalLight {  // Свет
                    color: "#afafff"  // со слегка голубоватым оттенком
                }

                Entity {
                    GoochMaterial {  // Материал
                        id: goochМaterial
                        diffuse: Qt.rgba(1, 1, 1, 1)
                    }
                    CuboidMesh {
                        id: planeMesh
                        xExtent: mySimulation.groundHalfExtents.x * 2
                        yExtent: mySimulation.groundHalfExtents.y * 2
                        zExtent: mySimulation.groundHalfExtents.z * 2
                    }
                    Transform {
                        id: planeTransform
                        // формируем трансформационную матрицу
                        matrix: {
                            var mat = Qt.matrix4x4();
                            mat.translate(mySimulation.groundPosition);
                            return mat;
                        }
                    }
                    components: [planeMesh, goochМaterial, planeTransform]
                }

                Entity {  // Сущность сферы
                    PhongMaterial {  // элемент материала
                        id: phongMaterial
                        ambient: Qt.rgba(0.3, 0.3, 0.3, 1.0)  // управляет способностью поверхности отражать окружающую среду
                        diffuse: Qt.rgba(1, 1, 1, 1)  // задает основной цвет поверхности объекта
                    }
                    SphereMesh {  // элемент геометрии объекта сферы
                        id: sphereMesh
                        radius: mySimulation.sphereRadius
                    }
                    Transform {
                        id: sphereTransform
                        // формируем трансформационную матрицу
                        matrix: {
                            var mat = Qt.matrix4x4();
                            mat.translate(mySimulation.spherePosition);
                            return mat;
                        }
                    }
                    components: [sphereMesh, phongMaterial, sphereTransform]
                }

            }
        }

    }  // MyQuickItem

}
