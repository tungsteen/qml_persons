#include "sortfilterproxymodel.h"

#include <QDateTime>
#include <QDebug>


SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
  : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
}

void SortFilterProxyModel::setSortOrder(Qt::SortOrder order)
{
    QSortFilterProxyModel::sort(0, order);
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
    return QSortFilterProxyModel::lessThan(left, right);
}

QByteArray SortFilterProxyModel::sortRole() const
{
    return m_sortRole;
}

void SortFilterProxyModel::setSortRole(const QByteArray &role)
{
    if (m_sortRole != role) {
        m_sortRole = role;

        auto roles = sourceModel()->roleNames();
        QSortFilterProxyModel::setSortRole(roles.key(role));

    }
}
