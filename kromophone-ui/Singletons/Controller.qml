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
        }
        
        _previousForm = currentForm
    }
}
