import QtQuick 2.0
pragma Singleton

Item {
    property Loader mainLoader
    property string currentForm: "StartupForm"
    property string _previousForm
    property string image: ":/Images/Resources/spectrum.jpg"
    
    onCurrentFormChanged: {
        console.log("Navigating from " + _previousForm + " to " + currentForm)
        
        if (currentForm == "SpectrumSonificationForm") {
            app.startFileSonification(":/Images/Resources/spectrum.jpg")
        } else if (currentForm == "ImageSonificationForm") {
            app.startFileSonification(image)
        } else if (currentForm == "CameraSonificationForm") {
            app.startCameraSonification()
        }
        
        _previousForm = currentForm
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
