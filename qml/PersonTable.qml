import QtQuick 2.5

PersonTableForm {
    Component.onCompleted: {
        resizeColumnsToContents()
    }

    onSortIndicatorColumnChanged: {
        personModel.sortRole = getColumn(sortIndicatorColumn).role;
    }

    onSortIndicatorOrderChanged: {
        personModel.sortOrder = sortIndicatorOrder;
    }
}
