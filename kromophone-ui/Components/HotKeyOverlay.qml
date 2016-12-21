import QtQuick 2.0
import "../Singletons"

Overlay {
    id: overlay

    property bool showingWiimote: false
    
    property var keys: [
        "s - Toggle Horizontal Sweep",
        "a - Toggle Color Averaging",
        "h - Hide Display",
        "x - Lock or Unlock Camera Exposure",
        "Up - Increase Color Average Size",
        "Down - Decrease Color Average Size",
        "Left - Decrease Sweep Area",
        "Right - Increase Sweep Area",
        "? - Toggle this help",
        "q - Back to main menu"
    ]
    
    property var wiimote: [
        "A - Lock or Unlock Camera Exposure",
        "B - Toggle Horizontal Sweep",
        "Home - Toggle Color Averaging",
        "Up - Increase Color Average Size",
        "Down - Decrease Color Average Size",
        "Left - Decrease Sweep Area",
        "Right - Increase Sweep Area",
    ]
    
    Column {
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 20
        spacing: 5
        
        Repeater {
            id: textRepeater
            model: overlay.keys
            
            StandardText {
                width: parent.width
                text: modelData
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
    
    TextButton {
        id: wiimoteButton
        text: "Wiimote Button Mappings"
        onClicked: showingWiimote = !showingWiimote
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
    }
    
    states: [
        State {
            when: showingWiimote
            PropertyChanges {
                target: textRepeater
                model: overlay.wiimote
            }
            PropertyChanges {
                target: wiimoteButton
                text: "Show Key Mappings"
            }
        }

    ]
}
