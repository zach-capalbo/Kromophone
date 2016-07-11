import QtQuick 2.0
import "../Components"
import "../Singletons"

FormBase {
    width: 640
    height: 480
    
    Column {
        
        anchors.centerIn: parent
        spacing: 20
        
        
        Repeater {
            model: ListModel {
                ListElement { desc: "Sonify Camera"; target: "CameraSonificationForm" }
                ListElement { desc: "Sonify Image File"; target: "SelectImageForm" }
                ListElement { desc: "Sonify Color Spectrum"; target: "SpectrumSonificationForm" }
            }
            
            TextButton {
                text: desc
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: Controller.currentForm = target
            }
        }
        
    }
}
