import QtQuick 2.0
pragma Singleton

QtObject {
    property int fontSize: 20
    property string fontFamily: "Open Sans"
    property int borderWidth: 1
    property color normalBg: "#333"
    property color normalFg: "#eee"
    property color engagedBg: "#544"
    property color activeBg: "#111"
    property color darkenedBg: "#000"
}
