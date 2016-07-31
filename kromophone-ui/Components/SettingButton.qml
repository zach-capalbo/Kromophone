import QtQuick 2.0

TextButton {
    id: settingButton
    width: parent.width
    property string setting
    property var source: app
    text: settingButton.setting + ":\n" + source.settings[setting]
    
    onClicked: {
        if (source.settings[setting] == true || source.settings[setting] == false)
        {
            source.settings[setting] = !source.settings[setting]
        }
    }
}
