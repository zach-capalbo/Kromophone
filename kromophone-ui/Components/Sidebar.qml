import QtQuick 2.0
import "../Singletons"

Rectangle {
    width: 200
    height: parent.height
    border.width: Style.borderWidth
    border.color: Style.normalFg
    color: Style.normalBg
    
    default property alias extra: c.data
    Column {
        id: c
        width: parent.width
    }
    
    Column {
        anchors.top: c.bottom
        width: parent.width
        ColorPreview { 
            width: parent.width - Style.borderWidth * 2
            x: Style.borderWidth
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
