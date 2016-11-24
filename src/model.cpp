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

    if (m_row != index.row()) {
        m_row = index.row();
        m_person = m_repo->getPersonAt(index.row());
    }

    switch( role ) {
        case Qt::UserRole + 1 + Id:
            return m_person->id();
        case Qt::UserRole + 1 + Title:
            return m_person->title();
        case Qt::UserRole + 1 + Firstname:
            return m_person->firstName();
        case Qt::UserRole + 1 + Lastname:
            return m_person->lastName();
        case Qt::UserRole + 1 + Company:
            return m_person->company();
        case Qt::UserRole + 1 + Street:
            return QString("%1 %2").arg(m_person->street(), m_person->streetNo()).trimmed();
        case Qt::UserRole + 1 + ZipCode:
            return m_person->zipCode();
        case Qt::UserRole + 1 + Location:
            return m_person->location();
        case Qt::UserRole + 1 + Phone:
            return QString("%1/%2").arg(m_person->phoneArea(), m_person->phoneNumber());

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
    int remainder = count - m_fetched;

    int rowsToAdd = qMin(10, remainder);
    beginInsertRows(parent, m_fetched, m_fetched + rowsToAdd - 1);
    m_fetched += rowsToAdd;
    endInsertRows();
}
