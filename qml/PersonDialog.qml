import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2

import persons 1.0

Window {
    id: dialog
    color: palette.window
    title: person.id >= 0 ? qsTr("Edit Person") : qsTr("New Person");
    modality: Qt.NonModal
    flags: Qt.Dialog
    visible: true

    width: mainContent.implicitWidth + 100
    height: mainContent.implicitHeight + 50
    minimumWidth:  Math.min(596, width)
    minimumHeight: Math.min(446, height)

    property alias person: form.person

    onClosing: destroy();

    SystemPalette {
        id: palette
    }

    ColumnLayout {
        id: mainContent
        anchors.fill: parent
        anchors.margins: 8

        PersonEdit {
            id: form
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight

            Button {
                id: cancelButton
                text: qsTr("Cancel")
                Layout.alignment: Qt.AlignRight

                onClicked: close()
            }

            Button {
                id: saveButton
                text: qsTr("Save")
                Layout.alignment: Qt.AlignRight

                onClicked: {
                    repository.upsertPerson(dialog.person);
                    close()
                }
            }
        }
    }
}
