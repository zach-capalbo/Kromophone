import QtQuick 2.0
pragma Singleton

Item {
    property Loader mainLoader
    property string currentForm: "StartupForm"
    property string _previousForm
    property string image: ":/Images/Resources/spectrum.jpg"
    property bool landscape: false
    property bool isPortrait: !landscape
    property string remoteHost: "raspberrypi.home"
    
    onCurrentFormChanged: {
        console.log("Navigating from " + _previousForm + " to " + currentForm)
        
        if (currentForm == "SpectrumSonificationForm") {
            app.startFileSonification(":/Images/Resources/spectrum.jpg")
        } else if (currentForm == "ImageSonificationForm") {
            app.startFileSonification(image)
        } else if (currentForm == "CameraSonificationForm") {
            startCameraTimer.start()
        } else if (currentForm == "RemoteControlForm") {
            app.connectToRemote(remoteHost);
        }
        
        _previousForm = currentForm
    }
    
    function stopSonification() {
        app.stopSonification()
        currentForm = "StartupForm"
    }
    
    Timer {
        id: startCameraTimer
        interval: 1
        repeat: false
        running: false
        onTriggered: app.startCameraSonification()
    }

    Connections {
        target: app
        onCameraSonificationStarted: currentForm = "CameraSonificationForm"
        onFileSonificationStarted: {
            if (file[0] == ':') {
                image = "qrc" + file;
            }
            else
            {
                image = file
            }

            currentForm = "ImageSonificationForm"
        }
    }
}
