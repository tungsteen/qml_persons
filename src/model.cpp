#include "model.h"
#include "repository.h"
#include "person.h"

#include <QDebug>

enum Section
{
    Id,
    Title,
    Firstname,
    Lastname,
    Company,
    Street,
    ZipCode,
    Location,
    Phone,
    SectionCount
};


Model::Model(QObject *parent)
  : QAbstractListModel(parent)
{
    m_roleNames.clear();
    m_roleNames.insert( Id              + Qt::UserRole + 1, QByteArrayLiteral( "id" ) );
    m_roleNames.insert( Title           + Qt::UserRole + 1, QByteArrayLiteral( "title" ) );
    m_roleNames.insert( Firstname       + Qt::UserRole + 1, QByteArrayLiteral( "firstname" ) );
    m_roleNames.insert( Lastname        + Qt::UserRole + 1, QByteArrayLiteral( "lastname" ) );
    m_roleNames.insert( Company         + Qt::UserRole + 1, QByteArrayLiteral( "company" ) );
    m_roleNames.insert( Street          + Qt::UserRole + 1, QByteArrayLiteral( "street" ) );
    m_roleNames.insert( ZipCode         + Qt::UserRole + 1, QByteArrayLiteral( "zipcode" ) );
    m_roleNames.insert( Location        + Qt::UserRole + 1, QByteArrayLiteral( "location" ) );
    m_roleNames.insert( Phone           + Qt::UserRole + 1, QByteArrayLiteral( "phone" ) );
}

Model::Model(bool canFetchMore, QObject *parent)
  : Model(parent)
{
    m_canFetchMore = canFetchMore;
}

void Model::setRepository(Repository *r)
{
    beginResetModel();
    if(m_repo) {
        m_repo->disconnect(this);
    }
    m_repo = r;

    connect(m_repo, &Repository::dataChanged, [&]() {
        beginResetModel();
        endResetModel();
    });

    endResetModel();
}

int Model::rowCount(const QModelIndex &parent) const
{
    if( !m_repo ) {
        return 0;
    }

    return m_canFetchMore ? m_fetched : m_repo->countPersons();
}


QVariant Model::data(const QModelIndex &index, int role) const
{
    if( !m_repo ) {
        return QVariant();
    }

    if (m_repo->countPersons() == 0) {
        return QVariant();
    }

    if( !index.isValid() ) {
        return QVariant();
    }

    QScopedPointer<Person> p(m_repo->getPersonAt(index.row()));

    switch( role ) {
        case Qt::UserRole + 1 + Id:
            return p->id();
        case Qt::UserRole + 1 + Title:
            return p->title();
        case Qt::UserRole + 1 + Firstname:
            return p->firstName();
        case Qt::UserRole + 1 + Lastname:
            return p->lastName();
        case Qt::UserRole + 1 + Company:
            return p->company();
        case Qt::UserRole + 1 + Street:
            return QString("%1 %2").arg(p->street(), p->streetNo()).trimmed();
        case Qt::UserRole + 1 + ZipCode:
            return p->zipCode();
        case Qt::UserRole + 1 + Location:
            return p->location();
        case Qt::UserRole + 1 + Phone:
            return QString("%1/%2").arg(p->phoneArea(), p->phoneNumber());

        default:
            break;
    }

    return QVariant();
}

bool Model::canFetchMore(const QModelIndex &parent) const
{
    if(!m_canFetchMore || parent.isValid()) {
        return false;
    }

    int count = m_repo->countPersons();
    return m_fetched < count;
}

void Model::fetchMore(const QModelIndex &parent)
{
    if(!m_canFetchMore || parent.isValid()) {
        return;
    }

    int count = m_repo->countPersons();
    int addRows = qMin(m_fetched + 10, count);
    if(addRows > 0) {
        beginInsertRows(parent, m_fetched, addRows - 1);
        m_fetched = addRows;
        endInsertRows();
    }
}
