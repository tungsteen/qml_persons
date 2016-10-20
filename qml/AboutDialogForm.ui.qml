import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    implicitWidth: 550
    implicitHeight: 400

    property string version
    property string author
    property Image logo

    FontLoader {
        id: fontMeriendaOne
        source: "qrc:/fonts/MeriendaOne-Regular.ttf"
    }

    Image {
        id: logo
        width: 120
        height: 120
        fillMode: Image.PreserveAspectFit
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
        source: parent.logo
    }

    Label {
        id: appName
        font.pointSize: 30
        font.family: fontMeriendaOne.name
        text: Qt.application.name
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: logo.right
        anchors.leftMargin: 16
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 16
    }

    Label {
        id: appVersion
        font.pointSize: 14
        font.family: fontMeriendaOne.name
        text:  Qt.application.version
        anchors.top: appName.bottom
        anchors.topMargin: 0
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: appName.horizontalCenter
    }

    TabView {
        anchors.top: logo.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.margins: 8

        Tab {
            title: qsTr("About")

            Item {
                TextArea {
                    anchors.fill: parent
                    anchors.margins: 12
                    readOnly: true
                    frameVisible: false
                    backgroundVisible: false
                    text: author
                }
            }
        }

        Tab {
            title: qsTr("Version")
            Item {
                TextArea {
                    anchors.fill: parent
                    anchors.margins: 12
                    readOnly: true
                    frameVisible: false
                    backgroundVisible: false
                    text: version
                }
            }
        }
    }
}
