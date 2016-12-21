import QtQuick 2.0

Item {
    property alias model: settings.model
    width: model.length * 75
    Row {
        height: parent.height
        Repeater {
            id: settings
            width: parent.width
            model: ["Red", "Green", "Blue", "Yellow", "White"]

            SettingSlider {
                width: 75
                height: parent.height
                setting: modelData
            }
        }
    }
}
