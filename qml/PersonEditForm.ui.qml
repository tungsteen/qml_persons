import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

import persons 1.0


Item {
    implicitWidth: 640
    implicitHeight: 480
    focus: true

    property alias title: title.text
    property alias firstName: firstName.text
    property alias lastName: lastName.text
    property alias company: company.text
    property alias street: street.text
    property alias streetNo: streetNo.text
    property alias zipCode: zipCode.text
    property alias location: location.text
    property alias birthday: birthday.text
    property alias phoneArea: phoneArea.text
    property alias phoneNumber: phoneNumber.text
    property alias faxArea: faxArea.text
    property alias faxNumber: faxNumber.text
    property alias mobileArea: mobileArea.text
    property alias mobileNumber: mobileNumber.text
    property alias mail: mail.text

    RowLayout {
        id: rowLayout
        anchors.fill: parent

        GroupBox {
            title: "Person"
            Layout.fillHeight: true
            Layout.fillWidth: true

            GridLayout {
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                columns: 2

                Label {
                    text: qsTr("Title:")
                }

                ComboBox {
                    id: title
                    property string text: "N/A"
                    editable: true;
                    model: ["N/A", "Mr.", "Ms."]
                    onTextChanged: {
                        currentIndex = find(title.text)
                    }
                    onCurrentTextChanged: {
                        title.text = currentText
                    }
                }

                Label {
                    text: qsTr("Name:")
                }

                RowLayout {
                    Layout.fillWidth: true

                    TextField {
                        id: firstName
                        placeholderText: qsTr("First name")
                    }

                    TextField {
                        id: lastName
                        placeholderText: qsTr("Last name")
                        Layout.fillWidth: true
                    }
                }

                Label {
                    text: qsTr("Company:")
                }

                TextField {
                    id: company
                    placeholderText: "Company Name"
                    Layout.fillWidth: true
                }

                Label {
                    text: qsTr("Street:")
                    Layout.fillWidth: true
                }

                RowLayout {
                    TextField {
                        id: street
                        placeholderText: qsTr("Street")
                        Layout.fillWidth: true
                    }
                    TextField {
                        id: streetNo
                        placeholderText: qsTr("No")
                    }
                }

                Label {
                    text: qsTr("Location:")
                }

                RowLayout {
                    TextField {
                        id: zipCode
                        placeholderText: qsTr("ZIP Code")
                    }
                    TextField {
                        id: location
                        placeholderText: qsTr("Location")
                        Layout.fillWidth: true
                    }
                }
                Label {
                    text: qsTr("Birthday:")
                }

                TextField {
                    id: birthday
                }
            }
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            GroupBox {
                id: groupBox1
                title: qsTr("Contact")
                Layout.fillHeight: true
                Layout.fillWidth: true

                GridLayout {
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.top: parent.top
                    columns: 2

                    Label {
                        text: qsTr("Phone:")
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        TextField {
                            id: phoneArea
                            placeholderText: qsTr("Area Code")
                        }
                        TextField {
                            id: phoneNumber
                            placeholderText: qsTr("Number")
                            Layout.fillWidth: true
                        }
                    }

                    Label {
                        text: qsTr("Mobile:")
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        TextField {
                            id: mobileArea
                            placeholderText: qsTr("Area Code")
                        }
                        TextField {
                            id: mobileNumber
                            placeholderText: qsTr("Number")
                            Layout.fillWidth: true
                        }
                    }

                    Label {
                        text: qsTr("Fax:")
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        TextField {
                            id: faxArea
                            placeholderText: qsTr("Area Code")
                        }
                        TextField {
                            id: faxNumber
                            placeholderText: qsTr("Number")
                            Layout.fillWidth: true
                        }
                    }

                    Label {
                        text: qsTr("Mail:")
                    }

                    TextField {
                        id: mail
                        Layout.fillWidth: true
                    }
                }
            }

            GroupBox {
                title: qsTr("Bank Account")
                Layout.fillHeight: true
                Layout.fillWidth: true

                GridLayout {
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.top: parent.top
                    columns: 2

                    Label {
                        text: qsTr("Institution:")
                    }

                    TextField {
                        id: bankInstitution
                        Layout.fillWidth: true
                    }

                    Label {
                        text: qsTr("IBAN:")
                    }

                    TextField {
                        id: bankIBAN
                        Layout.fillWidth: true
                    }

                    Label {
                        text: qsTr("BIC:")
                    }

                    TextField {
                        id: bankBIC
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
}
