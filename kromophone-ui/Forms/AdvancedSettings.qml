import QtQuick 2.0
import "../Components"
import "../Singletons"

Overlay {
    Flickable {
        contentHeight: column.height
        contentWidth: parent.width
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick

        Column {
            id: column
            anchors.horizontalCenter: parent.horizontalCenter

            SettingSlider {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 50
                height: 100
                setting: "saturationAdjustment"
                max: 5.0
            }

            TitleText{
                text: "Color Volumes"
            }

            Equalizer {
                height: 100
                anchors.horizontalCenter: parent.horizontalCenter
                model: ["Red", "Green", "Blue", "Yellow", "White"]
            }
        }
    }
}
