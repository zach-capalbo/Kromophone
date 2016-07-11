import QtQuick 2.0
pragma Singleton

QtObject {
    property Loader mainLoader
    property string currentForm: "StartupForm"
    property string _previousForm
    
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
    
    property string image: ":/Images/Resources/spectrum.jpg"
}
