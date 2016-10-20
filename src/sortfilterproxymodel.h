#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>


class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filterString READ filterString WRITE setFilterString NOTIFY filterStringChanged)

    public:
        explicit SortFilterProxyModel(QObject *parent = nullptr);

        QString filterString() const
        {
            return m_filterString;
        }

    public slots:
        void setFilterString(QString value);

    signals:
        void filterStringChanged();

    protected:
        bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
        bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

    private:
        QString m_filterString;
};


#endif
