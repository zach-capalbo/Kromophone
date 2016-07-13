import QtQuick 2.0
import "../Singletons"

Item {
    width: parent.width * 0.95
    height: parent.height * 0.95
    anchors.centerIn: parent
    
    Rectangle {
        anchors.fill: parent
        color: Style.normalBg
        opacity: 0.85
        radius: 10
        border.color: Style.normalFg
        border.width: Style.borderWidth
    }
    
    Column {
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 20
        spacing: 5
        
        Repeater {
            model: [
                "s - Toggle Horizontal Sweep",
                "a - Toggle Color Averaging",
                "h - Hide Display",
                "x - Toggle Autoexposure (RPI only)",
                "Up - Increase Color Average Size",
                "Down - Decrease Color Average Size",
                "Left - Decrease Sweep Area",
                "Right - Increase Sweep Area",
                "? - Toggle this help"
            ]
            
            StandardText {
                width: parent.width
                text: modelData
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
