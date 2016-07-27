import QtQuick 2.0
import "../Components"
import "../Singletons"

FormBase {
    Image {
        source: "../Images/Kromophone.png"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: 120
        height: 120
    }

    Column {
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 5
        spacing: Style.fontSize

        TitleText { text: "The Kromophone"; anchors.horizontalCenter: parent.horizontalCenter }

        Repeater {
            model: [
                "Version " + app.version,
                "http://kromophone.com",
                "https://github.com/zach-capalbo/Kromophone/",
                "© 2016 Zachary Capalbo <thekromophone@gmail.com>"
            ]
            StandardText { text: modelData; anchors.horizontalCenter: parent.horizontalCenter }
        }

        TextButton {
            text: "This program is free software\nView License (GPL)"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

}
