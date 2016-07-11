import QtQuick 2.0

Item {
    Column {
        anchors.fill: parent
        ColorPreview { 
            width: parent.width
        }
        
        Repeater {
            model: app.settingList
            SettingButton {
                setting: modelData
            }
        }
    }
}
