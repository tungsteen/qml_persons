import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

Window {
    id: dialog
    title: qsTr("About") + Qt.application.name
    color: palette.window

    modality: Qt.NonModal
    flags: Qt.Dialog

    visible: true

    width: mainContent.implicitWidth
    height: mainContent.implicitHeight

    minimumWidth:  Math.min(300, width)
    minimumHeight: Math.min(300, height)

    onClosing: {
        destroy();
    }

    SystemPalette {
        id: palette
    }

    ColumnLayout {
        id: mainContent
        anchors.fill: parent
        anchors.margins: 8

        AboutDialogForm {
            Layout.fillWidth: true
            Layout.fillHeight: true

            version: application.version
            author: qsTr("(c) 2016 Stefan Böhmann")
        }

        Button {
            id: closeButton
            text: qsTr("Close")
            Layout.alignment: Qt.AlignRight
            onClicked: close()
        }
    }
}

