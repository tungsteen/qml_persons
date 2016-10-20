import QtQuick 2.5
import QtQuick.Controls 1.4

TableView {
    implicitWidth: 800
    implicitHeight: 600

    sortIndicatorVisible: true

    TableViewColumn {
        role: "firstname"
        title: qsTr("First name")
    }
    TableViewColumn {
        role: "lastname"
        title: qsTr("Last name")
    }
    TableViewColumn {
        role: "company"
        title: qsTr("Company")
    }
    TableViewColumn {
        role: "street"
        title: qsTr("Street")
    }
    TableViewColumn {
        role: "zip"
        title: qsTr("ZIP Code")
    }
    TableViewColumn {
        role: "location"
        title: qsTr("Location")
    }
    TableViewColumn {
        role: "phone"
        title: qsTr("Phone")
    }
}
