import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import "../Components"

FormBase {
    id: main
    
    CameraCapture {
        id: camera
        width: main.width * 0.85
        height: parent.height
    }
    Sidebar {
        anchors.left: camera.right
        anchors.right: parent.right
    }
}
