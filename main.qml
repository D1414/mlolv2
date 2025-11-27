import QtQuick
import QtQuick.Controls
import Mastery 1.0

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("LoL Mastery Viewer")
    color: "#333333"

    RiotApi {
        id: riotApi
        onError_occurred: (msg) => console.log(msg)
        onFound_puuid: (puuid) => console.log("PUUID: " + puuid)
        onReceived_mastery: (json) => statusText.text = "Daten empfangen!"
        onChampionsMapChanged: {
            console.log("Mastery Daten erhalten!")
            for(const champ of championsMap){
               console.log(champ.name);
               console.log(champ.icon);
            }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 15
        width: 300

        TextField {
            id: nameField;
            placeholderText: "name";
            width: parent.width;
            text: "BestBear360";
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
            text: "RGAPI-5a7d506b-5e9d-4fe9-99f4-a9fb6cbc8d42";
        }

        Button {
            text: "Suchen"
            width: parent.width
            onClicked:{
                riotApi.search_summoner(nameField.text, tagField.text, apiKeyField.text)
            }
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

