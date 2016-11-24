#ifndef MODEL_H
#define MODEL_H

#include <QtCore/QAbstractListModel>

class Repository;

class Person;
class Model : public QAbstractListModel
{
    Q_OBJECT

    public:
        explicit Model(QObject *parent = nullptr);
        explicit Model(bool canFetchMore, QObject *parent = nullptr);

        void setRepository(Repository *r);

        QHash<int, QByteArray> roleNames() const override {
            return m_roleNames;
        }

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        bool canFetchMore(const QModelIndex &parent) const override;
        void fetchMore(const QModelIndex &parent) override;

    private:
        bool m_canFetchMore = false;
        int m_fetched = 0;
        QHash<int, QByteArray> m_roleNames;
        Repository *m_repo = nullptr;
        mutable int m_row = -1;
        mutable Person* m_person;
};

#endif
