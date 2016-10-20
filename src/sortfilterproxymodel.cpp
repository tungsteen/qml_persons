#include "sortfilterproxymodel.h"

#include <QDateTime>
#include <QDebug>


SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
  : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
}

void SortFilterProxyModel::setFilterString(QString value)
{
    value = value.toLower();
    if( m_filterString == value ) {
        return;
    }

    m_filterString = value;
    invalidateFilter();

    emit filterStringChanged();
}

bool SortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if( m_filterString.isEmpty() ) {
        return true;
    }

    for(int i = 0; i < sourceModel()->columnCount(); ++i) {
        QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);

        if( sourceModel()->data(index, Qt::DisplayRole).toString().toLower().contains( m_filterString ) ) {
            return true;
        }

        if( sourceModel()->data(index, Qt::EditRole).toString().toLower().contains( m_filterString ) ) {
            return true;
        }
    }

    QList<int> roleList = sourceModel()->roleNames().keys();
    for(int role : roleList) {
        QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

        if( sourceModel()->data(index, role).toString().toLower().contains( m_filterString ) ) {
            return true;
        }
    }

    return false;
}

bool SortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    if( leftData.type() == QVariant::DateTime ) {
        return leftData.toDateTime() < rightData.toDateTime();
    }
    else if( leftData.type() == QVariant::Date ) {
        return leftData.toDate() < rightData.toDate();
    }
    else if( leftData.type() == QVariant::Time ) {
        return leftData.toTime() < rightData.toTime();
    }

    return QString::localeAwareCompare(leftData.toString(), rightData.toString()) < 0;
}
