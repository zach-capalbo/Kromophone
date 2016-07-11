import QtQuick 2.0
import "../Singletons"

Rectangle {
    width: 200
    height: parent.height
    border.width: Style.borderWidth
    border.color: Style.normalFg
    color: Style.normalBg
    z: 10000
    Column {
        anchors.fill: parent
        ColorPreview { 
            width: parent.width
        }
        
        Repeater {
            model: app.settingList
            SettingButton {
                setting: modelData
                padding: 10
            }
        }
    }
}
