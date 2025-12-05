import QtQuick
import QtQuick.Controls
import QtQuick.Effects
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
        onChampionsChanged: {
            for(const champ of champions){
               console.log(champ.name);
               console.log("	id: " + champ.id);
               console.log("	icon: " + champ.icon);
               console.log("	level: " + champ.level);
               console.log("	points: " + champ.points);
            }
        }
    }

    Column {
        id: searchColumn
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 20
        spacing: 10
        width: 300
        z: 10

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
            text: "RGAPI-e10af07e-9660-4a8d-95d9-2a1cbc85a542";
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
    GridView {
        id: championGrid
        anchors.top: searchColumn.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20
        clip: true

        cellWidth: 160
        cellHeight: 160

        model: riotApi.champions

        delegate: Column {
            width: championGrid.cellWidth
            spacing: 5

            Item {
                width: 120
                height: 120
                anchors.horizontalCenter: parent.horizontalCenter

                HoverHandler {
                   id: hoverHandler
                   cursorShape: Qt.PointingHandCursor
                }
                Image {
                    id: champSrc
                    anchors.fill: parent
                    source: modelData.icon ? "https://ddragon.leagueoflegends.com/cdn/15.23.1/img/champion/" + modelData.icon : ""
                    visible: false
                }

                MultiEffect {
                    anchors.fill: parent
                    source: champSrc
                    saturation: modelData.level < 5 ? -1.0 : 0.0
                    opacity: modelData.level < 5 ? 0.6 : 1.0
                }

                Rectangle {
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "white"
                    border.width: 3
                    visible: hoverHandler.hovered
                }

            }
            Text{
                text: modelData.name
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
            }
        }
    }
}

