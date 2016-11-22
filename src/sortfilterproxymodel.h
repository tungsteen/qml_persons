#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>


class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filterString READ filterString WRITE setFilterString NOTIFY filterStringChanged)
    Q_PROPERTY(QByteArray sortRole READ sortRole WRITE setSortRole)
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder)

    public:
        explicit SortFilterProxyModel(QObject *parent = nullptr);

        QString filterString() const
        {
            return m_filterString;
        }
        QObject *source() const;
        void setSource(QObject *source);
        QByteArray sortRole() const;

    public slots:
        void setFilterString(QString value);
        void setSortRole(const QByteArray &role);
        void setSortOrder(Qt::SortOrder order);

    signals:
        void filterStringChanged();

    protected:
        bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
        bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

    private:
        QString m_filterString;
        QByteArray m_sortRole;
};


#endif
