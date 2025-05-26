import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: mainWindow
    visible: true
    flags: Qt.Window
    width: 600
    height: 400
    color: "#e3e3e3"

    property int rfcTextFontSize: 15

    Connections {
        target: rfcWorker
        function onPagesChanged() {
            rfcWorker.setCurrentRfcPage(0);
            pageListView.forceLayout();
        }

        function onCurrentRfcPageChanged() {
            pageListView.positionViewAtIndex(rfcWorker.currentPage, ListView.Center);
        }
    }

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: 10

        Navbar {
            id: navbar
            Layout.fillWidth: true
            height: 80
            settingsWindow: settingsWindow
        }

        RowLayout {
            id: textLayout
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 100

            ScrollView {
                id: rfcTextScrollView
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: parent.parent.width * 0.7
                ScrollBar.vertical.policy: ScrollBar.AsNeeded

                TextArea {
                    id: rfcText
                    height: parent.height
                    width: parent.width
                    padding: 10
                    text: rfcWorker.currentPageText
                    readOnly: true
                    wrapMode: TextArea.Wrap
                    font.family: "Courier New"
                    font.pixelSize: rfcTextFontSize
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            ScrollView {
                id: pagesPreview
                Layout.fillHeight: true
                Layout.preferredWidth: parent.parent.width * 0.1
                clip: true
                ScrollBar.vertical.policy: ScrollBar.AsNeeded
                visible: parent.width > 800

                ListView {
                    id: pageListView
                    width: parent.width
                    height: parent.height
                    model: rfcWorker.pages
                    spacing: 5

                    delegate: Loader {
                        width: pageListView.width - 20
                        height: 100
                        sourceComponent: Rectangle {
                            color: index === rfcWorker.currentPage ? "#cccccc" : "#ffffff"
                            border.color: "#000000"
                            border.width: 1
                            Text {
                                anchors.fill: parent
                                anchors.margins: 5
                                text: modelData
                                font.family: "Courier New"
                                font.pixelSize: 8
                                wrapMode: Text.Wrap
                                maximumLineCount: 7
                                elide: Text.ElideRight
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: rfcWorker.setCurrentRfcPage(index)
                                hoverEnabled: true
                                ToolTip {
                                    visible: parent.containsMouse
                                    text: "Page " + (index + 1)
                                    delay: 500
                                    timeout: 5000
                                }
                            }
                        }
                    }
                }
            }
        }


        Rectangle {
            color: "#919191"
            Layout.fillWidth: true
            Layout.minimumHeight: 40
            Layout.preferredHeight: 40
            radius: 15

            RowLayout {
                anchors.fill: parent

                Button {
                    text: "Previous"
                    enabled: rfcWorker.currentPage > 0
                    Layout.leftMargin: 20
                    onClicked: {
                        if (rfcWorker.currentPage > 0) {
                            rfcWorker.setCurrentRfcPage(rfcWorker.currentPage - 1);
                        }
                    }
                }

                // Spacer
                Item { Layout.fillWidth: true }

                Button {
                    text: "Next"
                    enabled: rfcWorker.currentPage < rfcWorker.pages.length - 1
                    Layout.rightMargin: 20
                    onClicked: {
                        if (rfcWorker.currentPage < rfcWorker.pages.length - 1) {
                            rfcWorker.setCurrentRfcPage(rfcWorker.currentPage + 1);
                        }
                    }
                }
            }
        }


        Shortcut {
            enabled: rfcWorker.pages.length > 0
            sequence: "Ctrl+H"
            onActivated: {
                navbar.visible = !navbar.visible
                pagesPreview.visible = !pagesPreview.visible
            }
        }
    }

    Shortcut {
        sequences: ["Right", "Down", "PgDown"]
        enabled: rfcWorker.currentPage < rfcWorker.pages.length - 1
        onActivated: rfcWorker.setCurrentRfcPage(rfcWorker.currentPage + 1);
    }

    Shortcut {
        sequences: ["Left", "Up", "PgUp"]
        enabled: rfcWorker.currentPage > 0
        onActivated: rfcWorker.setCurrentRfcPage(rfcWorker.currentPage - 1);
    }

    Shortcut {
        enabled: rfcWorker.pages.length > 0
        sequence: "Ctrl++"
        onActivated: {
            if (rfcTextFontSize < 15) {
                rfcTextFontSize++;
            }
        }
    }

    Shortcut {
        enabled: rfcWorker.pages.length > 0
        sequence: "Ctrl+-"
        onActivated: {
            if (rfcTextFontSize > 10) {
                rfcTextFontSize--;
            }
        }
    }

    Settings {
        id: settingsWindow
        mainWindow: mainWindow
    }
}
