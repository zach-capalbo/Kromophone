import QtQuick 2.0

TextButton {
    id: settingButton
    width: parent.width
    property string setting
    text: settingButton.setting + ":\n" + app.settings[setting]
}
