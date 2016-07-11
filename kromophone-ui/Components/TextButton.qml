import QtQuick 2.0
import "../Singletons"

Rectangle {
    id: r
    property alias text: t.text
    property string description
    property int padding: 30
    width: t.width + padding
    height: t.height + padding
    signal clicked()
    color: Style.normalBg
    
    border {
        width: Style.borderWidth
        color: Style.normalFg
    }
    
    Text {
        id: t
        anchors.centerIn: parent
        color: Style.normalFg
        font.pixelSize: Style.fontSize
    }
    
    MouseArea {
        id: m
        anchors.fill: parent
        hoverEnabled: true
        onClicked: r.clicked()
    }
    
    states: [
        State {
            when: m.pressed && m.containsMouse
            PropertyChanges {
                target: r
                color: Style.activeBg
            }
        },
        State {
            when: m.containsMouse
            PropertyChanges {
                target: r
                color: Style.engagedBg
            }
        }
    ]
    
    Accessible.role: Accessible.Button
    Accessible.name: t.text
    Accessible.description: r.description
    Accessible.onPressAction: r.clicked()
}
