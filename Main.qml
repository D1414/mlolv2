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

 /* 	MyTextField { id: nameField; width: parent.width; placeholderText: "Game Name" }
        MyTextField { id: tagField; width: parent.width; placeholderText: "Tag (z.B. EUW)" }
        MyTextField { id: apiKeyField; width: parent.width; placeholderText: "API Key"; echoMode: TextInput.Password }
*/
        TextField {
            id: nameField;
            placeholderText: "name";
            width: parent.width;
        }
        TextField {
            id: tagField;
            placeholderText: "tag";
            width: parent.width;
        }
        TextField {
            id: apiKeyField;
            placeholderText: "API key";
            width: parent.width;
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
