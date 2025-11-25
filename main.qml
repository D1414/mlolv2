import QtQuick
import QtQuick.Controls
import Mastery 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("LoL Mastery Viewer")
    color: "#333333"

    RiotApi {
        id: riotApi
        onError_occurred: (msg) => console.log(msg)
        onFound_puuid: (puuid) => console.log("PUUID: " + puuid)
        onReceived_mastery: (json) => statusText.text = "Daten empfangen!"
    }

    Column {
        anchors.centerIn: parent
        spacing: 15
        width: 300

        TextField {
            id: nameField;
            placeholderText: "name";
            width: parent.width;
            text: "Odnamra";
        }
        TextField {
            id: tagField;
            placeholderText: "tag";
            width: parent.width;
            text: "euw";
        }
        TextField {
            id: apiKeyField;
            placeholderText: "API key";
            width: parent.width;
            text: "RGAPI-61ae7e68-6671-4b5e-8ad5-d2efbb615079";
        }

        Button {
            text: "Suchen"
            width: parent.width
            onClicked: riotApi.search_summoner(nameField.text, tagField.text, apiKeyField.text)
        }

        Text {
            id: statusText
            text: "Bereit"
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }
    }
}
