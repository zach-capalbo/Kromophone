import QtQuick 2.0
import "../Singletons"

Item {
    clip: true
    
    Image {
        anchors.centerIn: parent
        id: i
        property int t: 0
        source: "image://preview/" + t
        
        Timer {
            onTriggered: i.t = i.t + 1
            interval: 100
            running: true
            repeat: true
        }
    }
}
