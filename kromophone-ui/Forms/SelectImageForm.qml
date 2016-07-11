import QtQuick 2.2
import QtQuick.Dialogs 1.0
import "../Singletons"

FileDialog {
    id: fileDialog
    title: "Please choose a file"
    nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
    selectMultiple: false
    onAccepted: {
        Controller.image =  fileDialog.fileUrl
        Controller.currentForm = "ImageSonificationForm"
    }
    onRejected: {
        Controller.currentForm = "StartupForm"
    }
    Component.onCompleted: visible = true
}
