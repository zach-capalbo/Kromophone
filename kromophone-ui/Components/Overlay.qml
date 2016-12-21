import QtQuick 2.0
import "../Singletons"

Item {
    id: overlay
    width: parent.width * 0.95
    height: parent.height * 0.95
    anchors.centerIn: parent
    clip: true

    Rectangle {
        anchors.fill: parent
        color: Style.normalBg
        opacity: 0.85
        radius: 10
        border.color: Style.normalFg
        border.width: Style.borderWidth
    }
}
