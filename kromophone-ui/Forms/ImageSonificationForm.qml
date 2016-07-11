import QtQuick 2.2
import QtQuick.Dialogs 1.0
import "../Components"
import "../Singletons"

SonificationForm {
    id: form
    property alias source: image.source
    Image {
        id: image
        anchors.centerIn: parent
        source: Controller.image
        
        MouseArea {
            width: parent.width - 1
            height: parent.height - 1
            hoverEnabled: true
            cursorShape: Qt.CrossCursor
            onPositionChanged: app.onMouseImageHover(mouse.x, mouse.y)
        }
    }
}
