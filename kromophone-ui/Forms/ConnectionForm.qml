import QtQuick 2.0
import "../Components"
import "../Singletons"

FormBase {
    Column {
        anchors.fill: parent
        anchors.margins: 50
        spacing: 10

        TitleText {
            text: "Connect To:"
        }

        StandardTextField {
            placeholderText: "Host"
            width: parent.width
            onTextChanged: {
                Controller.remoteHost = text
            }
        }

        TextButton {
            text: "Connect"
            onClicked: Controller.currentForm = "RemoteControlForm"
        }
    }
}
