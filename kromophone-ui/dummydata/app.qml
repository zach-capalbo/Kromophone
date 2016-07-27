import QtQuick 2.0

Item {
    property color color: "green"
    property QtObject settings: _setting
    property var settingList: { var l = []; for (var prop in _setting) { l.push(prop); }; return l; }
    property string version: "6.6.6"
    
    Behavior on color { ColorAnimation {  duration: 200  } }
    Timer {
        running: true
        repeat: true
        interval: 500
        onTriggered: color = Qt.rgba(Math.random(255), Math.random(255), Math.random(255), 1)
    }
    
    function onMouseImageHover(x, y) {}
    
    function startFileSonification(p) {}
    
    QtObject {
        id: _setting
        
        property bool sweep: false
    }
}
