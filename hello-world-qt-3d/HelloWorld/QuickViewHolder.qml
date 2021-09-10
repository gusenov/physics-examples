import QtQuick 2.0
import QtQuick.Window 2.15
import com.example.MyQuickView 1.0

Item {
    id: item

    onVisibleChanged: {
        myQuickView.visible = item.visible
    }

    MyQuickView {
        id: myQuickView

        width: 640
        height: 480
        visible: false
        title: qsTr("Hello World")

        source: "QuickItemHolder.qml"

        Component.onCompleted: {
            myQuickView.visible = true
        }
    }

}
