import QtQuick 2.0
import "Singletons"

Item {
    id: mainContainer
    width: 800
    height: 600
    anchors.fill: parent
    rotation: app.settings.rotate
    
    Loader {
        id: formLoader
        source: "Forms/" + Controller.currentForm + ".qml"
        anchors.fill: parent
    }
    
    Component.onCompleted: {
        Controller.mainLoader = formLoader
        Controller.landscape = mainContainer.width > mainContainer.height
    }
}
