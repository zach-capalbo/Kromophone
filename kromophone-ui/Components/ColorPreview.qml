import QtQuick 2.0

Rectangle {
    color: app.color
    width: 64
    height: 64
    
    Text {
        anchors.centerIn: parent
        text: app.color
    }
}
