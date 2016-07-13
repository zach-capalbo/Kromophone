import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import "../Components"
import "../Singletons"

FormBase {
    id: main
    default property alias display: item.data
    
    Rectangle {
        id: item
        anchors.right: sidebar.left
        anchors.left: parent.left
        height: parent.height
        color: Style.darkenedBg
    }
    
    Rectangle {
        anchors.fill: item
        color: Style.darkenedBg
        visible: app.settings.hiddenDisplay
    }
    
    Sidebar {
        id: sidebar
        anchors.right: parent.right
        z: 1000
        
        TextButton {
            text: "Show Hot Keys"
            width: parent.width
            onClicked: {
                help.visible = !help.visible
            }
        }
    }
    
    HotKeyOverlay {
        id: help
        visible: false
        z: 2000
    }
    
    Keys.enabled: true
    Keys.onReleased: {
        console.log(event.key)
        if (event.text == "s")
        {
            app.settings.sweep = !app.settings.sweep
        } 
        else if (event.text == "a")
        {
            app.settings.average = !app.settings.average
        }
        else if (event.text == "h")
        {
            app.settings.hiddenDisplay = !app.settings.hiddenDisplay
        }
        else if (event.text == "x")
        {
            app.settings.autoExposure = !app.settings.autoExposure
        }
        else if (event.text == "?")
        {
            help.visible = !help.visible
        }

        console.log(event.text);
    }
    
    Keys.onUpPressed: {
        app.settings.averageSize += 3
    }
    
    Keys.onDownPressed: {
        if (app.settings.averageSize > 3)
            app.settings.averageSize -= 3
    }
    
    Keys.onRightPressed: {
        app.settings.sweepSize += 3
    }
    
    Keys.onLeftPressed: {
        app.settings.sweepSize -= 3
    }

    focus: true
    
    Component.onCompleted: {
        main.forceActiveFocus()
    }
}
