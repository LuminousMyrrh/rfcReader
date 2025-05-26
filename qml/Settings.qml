import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: root
    minimumWidth: 400
    minimumHeight: 300
    title: "Settings"
    modality: Qt.ApplicationModal
    flags: Qt.WindowModal | Qt.SubWindow
    visible: false
    property ApplicationWindow mainWindow: null
    x: mainWindow ? mainWindow.x + (mainWindow.width - width) / 2 : 0
    y: mainWindow ? mainWindow.y + (mainWindow.height - height) / 2 : 0

    RowLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: 10

        ColumnLayout {
            id: leftSide
            Layout.fillHeight: true

            Rectangle {
                id: generalField
                Layout.fillWidth: true
                Layout.preferredHeight: 100
                color: "#f0f0f0"
                radius: 5

                Label {
                    text: "General"
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.margins: 10
                    font.bold: true
                }

                Label {
                    text: "Advanced"
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.margins: 10
                    font.bold: true
                }

                TextField {
                    anchors.centerIn: parent
                    width: parent.width - 20
                    placeholderText: "Enter setting value"
                }
            }
        }

        ColumnLayout {
            id: rightSide
            Layout.fillHeight: true

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 100
                color: "#f0f0f0"
                radius: 5
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Button {
                    text: "OK"
                    onClicked: {
                        console.log("Settings saved")
                        root.visible = false
                    }
                }

                Button {
                    text: "Cancel"
                    onClicked: {
                        console.log("Settings canceled")
                        root.visible = false
                    }
                }
            }
        }
    }
}
