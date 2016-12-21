import QtQuick 2.0
import "../Singletons"

Item {
    id: slider
    width: parent == null ? parent.width : 30
    height: parent == null ? parent.height : 70
    property string setting: "Test"
    property var source: app
    property real value: source.settings[setting]
    property real max: 1.0
    property real min: 0.0
    property real percent: (slider.value - slider.min) / (slider.max - slider.min)

    StandardText {
        id: label
        text: slider.setting
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: barBg
        color: Style.normalBg
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: label.bottom
        anchors.margins: 3
        border.color: Style.normalFg
        border.width: Style.borderWidth
        Rectangle {
            id: fill
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: slider.percent * parent.height
            color: Style.normalFg
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: false
            preventStealing: true
            onClicked: {
                source.settings[setting] = inBounds(1.0 - mouse.y / height)
            }
            onMouseYChanged: {
                if (pressed) {
                    source.settings[setting] = inBounds(1.0 - Math.max(0.0, Math.min(1.0, mouse.y / height)))
                }
            }

            function inBounds(val)
            {
                return val * (slider.max - slider.min) + slider.min;
            }
        }

        Text {
            anchors.centerIn: parent
            color: slider.percent > 0.5 ? Style.darkenedBg : Style.engagedFg
            text: value.toFixed(2);
        }
    }

    states: [
        State {
            when: mouseArea.containsMouse
            PropertyChanges {
                target: barBg
                color: Style.activeBg
            }
            PropertyChanges {
                target: fill
                color: Style.engagedFg
            }
        }

    ]
}
