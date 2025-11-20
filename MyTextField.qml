import QtQuick
import QtQuick.Controls

TextField {
    id: control
    selectByMouse: true
    color: "black"
    background: Rectangle { color: "white"; radius: 4 }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.IBeamCursor
        acceptedButtons: Qt.RightButton
        onClicked: contextMenu.popup()
    }

    Menu {
        id: contextMenu
        MenuItem {
            text: "Einfügen"
            enabled: control.canPaste
            onTriggered: {
                control.forceActiveFocus()
                control.paste()
            }
        }
        MenuItem {
            text: "Kopieren"
            enabled: control.selectedText.length > 0
            onTriggered: {
                control.forceActiveFocus()
                control.copy()
            }
        }
    }
}
