import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

import persons 1.0

ComboBox {
    id: title
    property string text
    editable: true;
    model: ["N/A", "Mr.", "Ms."]
    onTextChanged: {
        var idx = find(title.text)
        console.log(idx + " - " + title.text)
        if(idx !== currentIndex) {
            currentIndex = idx
        }
    }
    onCurrentIndexChanged: {
        if(title.text !== currentText) {
            title.text = currentText
        }
    }
}
