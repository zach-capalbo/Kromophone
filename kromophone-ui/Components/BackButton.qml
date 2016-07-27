import QtQuick 2.0
import "../Singletons"

TextButton {
    anchors.top: parent.top
    anchors.right: parent.right
    text: "<-"
    onClicked: Controller.currentForm = "StartupForm"
}
