import QtQuick 2.0
import "../Components"

SonificationForm {
    Loader {
        source: app.isAndroid ? "../Components/CameraCapture.qml" : "../Components/ImagePreview.qml"
        id: camera
        width: parent.width
        height: parent.height
    }
}
