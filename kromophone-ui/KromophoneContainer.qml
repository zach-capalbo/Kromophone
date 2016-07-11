import QtQuick 2.0
import "Singletons"

Item {
    width: 800
    height: 600
    anchors.fill: parent
    
    Loader {
        id: formLoader
        source: "Forms/" + Controller.currentForm + ".qml"
        anchors.fill: parent
    }
    
    Component.onCompleted: {
        Controller.mainLoader = formLoader
    }
}
