import QtQuick 2.0
import "../Components"

FormBase {
    property alias source: image.source
    Image {
        id: image
        anchors.centerIn: parent
        
        MouseArea {
            width: parent.width - 1
            height: parent.height - 1
            hoverEnabled: true
            cursorShape: Qt.CrossCursor
            onPositionChanged: app.onMouseImageHover(mouse.x, mouse.y)
        }
    }
    
    Sidebar {        
        anchors.left: image.right
        anchors.right: parent.right
    }
}
