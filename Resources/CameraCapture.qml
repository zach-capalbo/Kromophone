import QtQuick 2.0
import QtMultimedia 5.4

Rectangle {
    id : cameraUI

    anchors.fill: parent

    color: "green"
    Camera {
        id: camera
    
        objectName: "qrCameraQML"
        viewfinder {
             resolution: "640x480"
        }
        captureMode: Camera.CaptureViewfinder
        Component.onCompleted: {
        }
    }

    
    VideoOutput {
        id: viewfinder

        x: 0
        y: 0
        width: parent.width
        height: parent.height

        source: camera
        autoOrientation: true
    }
}
