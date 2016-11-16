import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1


ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600
    title: qsTr("Persons")

    Component {
        id: aboutDialogComponent
        AboutDialog {}
    }

    Component {
        id: personDialogComponent
        PersonDialog {}
    }

    // File actions
    Action {
        id: importDataAction
        text: qsTr("Import data...")
        onTriggered: fileImportDialog.visible = true
    }

    Action {
        id: exportDataAction
        text: qsTr("Export data...")
        onTriggered: fileExportDialog.visible = true
    }

    Action {
        id: deleteDataAction
        text: qsTr("Delete data")
        onTriggered: repository.purge()
    }

    Action {
        id: quitAction
        text: qsTr("E&xit")
        shortcut: StandardKey.Quit
        iconSource: "qrc:/icons/application-exit.svg"
        onTriggered: Qt.quit();
    }

    // Edit actions
    Action {
        id: newPersonAction
        text: qsTr("New Person...")
        shortcut: StandardKey.New
        iconSource: "qrc:/icons/document-new.svg"

        onTriggered: {
            var dialog = personDialogComponent.createObject(root);
            dialog.open
        }
    }
    Action {
        id: editPersonAction
        text: qsTr("Edit Person...")
        //shortcut:
        iconSource: "qrc:/icons/document-edit.svg"

        onTriggered: {
            var dialog = personDialogComponent.createObject(root);
            dialog.person = repository.getPersonAt(personTable.selectedRow);
            dialog.open;
        }
    }
    Action {
        id: deletePersonAction
        text: qsTr("Delete Person...")
        iconSource: "qrc:/icons/trash-empty.svg"

        onTriggered: {
            deleteDialog.visible = true
        }
    }

    Action {
        id: searchAction
        text: qsTr("Find...")
        shortcut: StandardKey.Find
        iconSource: "qrc:/icons/edit-find.svg"

        onTriggered: {
            searchField.visible = !searchField.visible
            searchField.selectAll()
            searchField.forceActiveFocus()
        }
    }

    // Help action
    Action {
        id: aboutAction
        text: qsTr("&About ") + Qt.application.name
        iconSource: "qrc:/icons/help-about.svg"
        onTriggered: {
            aboutDialogComponent.createObject(root);
        }
    }


    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem { action: importDataAction }
            MenuItem { action: exportDataAction }
            MenuItem { action: deleteDataAction }
            MenuItem { action: quitAction }
        }

        Menu {
            title: qsTr("&Edit")
            MenuItem { action: newPersonAction }
            MenuItem { action: editPersonAction }
            MenuItem { action: deletePersonAction }
            MenuItem { action: searchAction }
        }

        Menu {
            title: qsTr("&Help")
            MenuItem { action: aboutAction }
        }
    }

    toolBar:ToolBar {
        RowLayout {
            anchors.fill: parent

            ToolButton { action: newPersonAction }

            ToolButton { action: editPersonAction }

            Item { width: 6 }

            ToolButton { action: deletePersonAction }

            Item { Layout.fillWidth: true }

            ToolButton {
                action: searchAction

                onClicked: {
                    if( hovered && searchField.text != "" ) {
                        console.log("ToolButton searchAction")
                        searchField.text = ""
                        searchField.visible = false
                    }
                }
            }

            TextField {
                id: searchField
                visible: false
                placeholderText: qsTr("search")
                Layout.alignment: Qt.AlignRight

                Keys.onReleased: {
                    if( event.key === Qt.Key_Escape ) {
                        if( searchField.text != "" ) {
                            searchField.text = ""
                        }
                        else {
                            visible = false
                        }
                        event.accepted = true
                    }

                    if( event.key === Qt.Key_Return || event.key === Qt.Key_Enter ) {
                        nextItemInFocusChain().forceActiveFocus()
                        event.accepted = true
                    }
                }

                onTextChanged: {
                    personModel.filterString = searchField.text
                }

                onActiveFocusChanged: {
                    if( !activeFocus && searchField.text == "" ) {
                        visible = false
                    }
                }
            }
        }
    }

    PersonTable {
        id: personTable
        anchors.fill: parent
        model: personModel
        property int selectedRow

        onClicked: {
            personTable.selectedRow = row
        }

        onDoubleClicked: {
            var dialog = personDialogComponent.createObject(root);
            dialog.person = repository.getPersonAt(row);
            dialog.open
        }
    }

    MessageDialog {
        id: deleteDialog
        title: "Delete?"
        text: "Are you sure?"
        visible: false
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        onAccepted: {
            var p = repository.getPersonAt(personTable.selectedRow);
            repository.removePersonById(p.id);
            visible = false;
        }
        onRejected: visible = false;
    }

    FileDialog {
        id: fileImportDialog
        title: "Please choose a file"
        folder: shortcuts.home
        selectMultiple: false
        onAccepted: {
            console.log("You chose: " + fileImportDialog.fileUrl)
            repository.importData(fileImportDialog.fileUrl)
            visible = false
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = false
    }

    FileDialog {
        id: fileExportDialog
        title: "Please choose a file"
        folder: shortcuts.home
        selectMultiple: false
        selectExisting: false
        onAccepted: {
            console.log("You chose: " + fileExportDialog.fileUrl)
            repository.exportData(fileExportDialog.fileUrl)
            visible = false
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = false
    }

}
