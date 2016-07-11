import QtQuick 2.0
import QtMultimedia 5.4

Rectangle {
    id : cameraUI
    Camera {
        id: camera
    
        objectName: "qrCameraQML"
        viewfinder {
             resolution: "640x480"
        }
        captureMode: Camera.CaptureViewfinder
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
    
    Rectangle {
        id: crosshair1
        color: "white"
        anchors.centerIn: parent
        width: 1
        height: Math.min(parent.width, parent.height) * 0.05
    }
    Rectangle {
        color: "white"
        anchors.centerIn: parent
        width: crosshair1.height
        height: 1
    }
}
