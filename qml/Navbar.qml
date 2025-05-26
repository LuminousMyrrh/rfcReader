import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    width: parent ? parent.width : 400
    height: 80
    Layout.fillWidth: true

    property Window settingsWindow: null

    Rectangle {
        id: navBar
        width: parent.width
        height: parent.height
        color: "#919191"
        radius: 10

        RowLayout {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 10

            // Button {
            //     text: "Settings"
            //     Layout.alignment: Qt.AlignVCenter
            //     background: Rectangle {
            //         color: "#b1b2b5"
            //         radius: 8
            //     }
            //     padding: 10

            //     onClicked: {
            //         if (root.settingsWindow) {
            //             root.settingsWindow.visible = true
            //         } else {
            //             console.log("Error: Settings window not defined")
            //         }
            //     }
            // }

            Item {
                Layout.fillWidth: true
            }

            TextField {
                id: inputArea
                Layout.preferredWidth: parent.width / 2
                Layout.maximumWidth: 200
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                placeholderText: "Search rfc by it's number"
                validator: IntValidator { bottom: 1; top: 9999 }
                background: Rectangle {
                    color: "#b1b2b5"
                    radius: 8
                }
                padding: 10

                onAccepted: {
                    if (acceptableInput) {
                        let url = "https://www.rfc-editor.org/rfc/rfc" + text + ".txt"
                        if (typeof networkManager !== "undefined") {
                            rfcWorker.setCurrentRfcNumber(text);
                            networkManager.sendRequest(url)
                        } else {
                            console.log("Error: networkManager is not defined")
                        }
                    } else {
                        console.log("Invalid RFC number")
                    }
                }
            }
        }
    }
}
