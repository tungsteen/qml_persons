#include "repository.h"

#include "person.h"

#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtCore/QStandardPaths>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtCore/QDebug>
#include <QUrl>

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>


Repository::Repository(QObject *parent)
  : QObject(parent)
{
    initDb();
}

void Repository::purge()
{
    QSqlQuery q( QStringLiteral("DELETE FROM person") );
    if( !q.exec() ) {
        qDebug() << q.lastError().text();
    }

    emit dataChanged();
}

int Repository::countPersons() const
{
    QSqlQuery q( QStringLiteral("SELECT COUNT(id) FROM person") );
    if( !q.next() ) {
        qDebug() << q.lastError().text();
        return 0;
    }

    return q.value(0).toInt();
}

Person* Repository::getPersonAt(int index) const
{
    QSqlQuery q( QString("SELECT * FROM person ORDER BY id LIMIT 1 OFFSET %1").arg(index) );
    if(!q.next()) {
        qDebug() << q.lastError().text();
    }

    return parsePerson(q);
}

Person* Repository::getPersonById(int id) const
{
    QSqlQuery q( QString("SELECT * FROM person ORDER BY id LIMIT 1 OFFSET %1" ).arg(id) );
    if(!q.next()) {
        qDebug() << q.lastError().text();
    }

    return parsePerson(q);
}

void Repository::upsertPerson(Person *p)
{
    if(!p) {
        qDebug() << "argument is a nullptr.";
        return;
    }

    if(p->id() >= 0) {
        updatePerson(p);
    }
    else {
        addPerson(p);
    }
}

void Repository::addPerson(Person *p)
{
    if(!p) {
        qDebug() << "argument is a nullptr.";
        return;
    }

    if(p->isEmpty()) {
        return;
    }

    static const char* insert_person = R"<<(
        INSERT INTO person (
            title, firstname, lastname, company, street, street_no, zip_code,
            location, birthday, phone_area, phone_number, mobile_area, mobile_number,
            fax_area, fax_number, mail, institution, iban, bic, notes,
            created_at
        )
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    )<<";

    QSqlQuery q;
    if( !q.prepare(insert_person) ) {
        qDebug() << q.lastError().text()  << q.lastQuery();
        return;
    }

    q.addBindValue(p->title());
    q.addBindValue(p->firstName());
    q.addBindValue(p->lastName());
    q.addBindValue(p->company());
    q.addBindValue(p->street());
    q.addBindValue(p->streetNo());
    q.addBindValue(p->zipCode());
    q.addBindValue(p->location());
    q.addBindValue(p->birthday().toJulianDay());
    q.addBindValue(p->phoneArea());
    q.addBindValue(p->phoneNumber());
    q.addBindValue(p->mobileArea());
    q.addBindValue(p->mobileNumber());
    q.addBindValue(p->faxArea());
    q.addBindValue(p->faxNumber());
    q.addBindValue(p->mail());
    q.addBindValue(p->institution());
    q.addBindValue(p->IBAN());
    q.addBindValue(p->BIC());
    q.addBindValue(p->notes());
    q.addBindValue(p->createdAt().toTime_t());

    if(!q.exec()) {
        qDebug() << q.lastError().text();
    }

    p->setId(q.lastInsertId().toInt());

    emit dataChanged();
}

void Repository::updatePerson(Person *p)
{
    if(!p) {
        qDebug() << "argument is a nullptr.";
        return;
    }

    static const char* update_person = R"<<(
        UPDATE person SET
            title         = ?,
            firstname     = ?,
            lastname      = ?,
            company       = ?,
            street        = ?,
            street_no     = ?,
            zip_code      = ?,
            location      = ?,
            birthday      = ?,
            phone_area    = ?,
            phone_number  = ?,
            mobile_area   = ?,
            mobile_number = ?,
            fax_area      = ?,
            fax_number    = ?,
            mail          = ?,
            institution   = ?,
            iban          = ?,
            bic           = ?,
            notes         = ?,
            created_at    = ?,
            updated_at    = ?
        WHERE id = ?;
    )<<";

    QSqlQuery q;
    if( !q.prepare(update_person) ) {
        qDebug() << q.lastError().text()  << q.lastQuery();
        return;
    }

    q.addBindValue(p->title());
    q.addBindValue(p->firstName());
    q.addBindValue(p->lastName());
    q.addBindValue(p->company());
    q.addBindValue(p->street());
    q.addBindValue(p->streetNo());
    q.addBindValue(p->zipCode());
    q.addBindValue(p->location());
    q.addBindValue(p->birthday().toJulianDay());
    q.addBindValue(p->mail());
    q.addBindValue(p->phoneArea());
    q.addBindValue(p->phoneNumber());
    q.addBindValue(p->mobileArea());
    q.addBindValue(p->mobileNumber());
    q.addBindValue(p->faxArea());
    q.addBindValue(p->faxNumber());
    q.addBindValue(p->institution());
    q.addBindValue(p->IBAN());
    q.addBindValue(p->BIC());
    q.addBindValue(p->notes());
    q.addBindValue(p->createdAt().toTime_t());
    q.addBindValue(QDateTime::currentDateTime().toTime_t());

    q.addBindValue(p->id());

    if(!q.exec()) {
        qDebug() << q.lastError().text()  << q.lastQuery();
    }

    emit dataChanged();
}

void Repository::removePerson(Person *p)
{
    QSqlQuery q( QString("DELETE FROM person WHERE id = %1").arg(p->id()) );
    if(!q.exec()) {
        qDebug() << "failed to remove Person.";
    }

    emit dataChanged();
}

void Repository::removePersonById(int id)
{
    QSqlQuery q( QString("DELETE FROM person WHERE id = %1").arg(id));
    if(!q.exec()) {
        qDebug() << "failed to remove Person.";
    }

    emit dataChanged();
}

void Repository::exportData(const QUrl &fileUrl)
{
    auto fileName = fileUrl.toLocalFile();
    exportData(fileName);
}

bool Repository::exportData(const QString &fileName)
{
    if(fileName.isEmpty() || QFile::exists(fileName)) {
        qDebug() << "File" << fileName << "exists.";
        return false;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not write to file:" << fileName;
        return false;
    }


    int count = countPersons();

    QJsonArray array;
    for(int i = 0; i < count; ++i) {
        QScopedPointer<Person> p( getPersonAt(i) );
        array.append(p->toJson());
    }

    QJsonDocument doc;
    doc.setArray(array);

    file.write(doc.toJson());
    file.close();

    return true;
}

void Repository::importData(const QUrl &fileUrl)
{
    auto fileName = fileUrl.toLocalFile();
    if (importData(fileName)) {
        emit dataChanged();
    }
}

bool Repository::importData(const QString &fileName)
{
    if(fileName.isEmpty() || !QFile::exists(fileName)) {
        qDebug() << "File" << fileName << "does not exists.";
        return false;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not read file:" << fileName;
        return false;
    }

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
    file.close();

    if(err.error != QJsonParseError::NoError) {
        qDebug() << "Parser error:" << err.errorString();
        return false;
    }

    QJsonArray array = doc.array();
    foreach(const QJsonValue v, array) {
        QScopedPointer<Person> p(new Person(v.toObject()));
        if(!p->isEmpty()) {
            addPerson(p.data());
        }
    }

    return true;
}

Person* Repository::parsePerson(const QSqlQuery &q) const
{

    Person *p = new Person;

    if( !q.isValid() ) {
        qDebug() << "Invalid QSqlQuery instance";
        return p;
    }

    p->setId( q.value("id").toInt() );
    p->setTitle( q.value("title").toString() );
    p->setFirstName( q.value("firstname").toString() );
    p->setLastName( q.value("lastname").toString() );
    p->setCompany( q.value("company").toString() );
    p->setStreet( q.value("street").toString() );
    p->setStreetNo( q.value("street_no").toString() );
    p->setZipCode( q.value("zip_code").toString() );
    p->setLocation( q.value("location").toString() );
    p->setBirthday( QDate::fromJulianDay(q.value("birthday").toLongLong()) );
    p->setPhoneArea( q.value("phone_area").toString() );
    p->setPhoneNumber( q.value("phone_number").toString() );
    p->setMobileArea( q.value("mobile_area").toString() );
    p->setMobileNumber( q.value("mobile_number").toString() );
    p->setFaxArea( q.value("fax_area").toString() );
    p->setFaxNumber( q.value("fax_number").toString() );
    p->setMail( q.value("mail").toString() );
    p->setInstitution( q.value("institution").toString() );
    p->setIBAN( q.value("iban").toString() );
    p->setBIC( q.value("bic").toString() );
    p->setNotes( q.value("notes").toString() );
    p->setCreatedAt( QDateTime::fromTime_t( q.value("created_at").toUInt() ) );
    p->setUpdatedAt( QDateTime::fromTime_t( q.value("updated_at").toUInt() ) );

    return p;
}

bool Repository::initDb()
{
    static const char* create_person = R"<<(
CREATE TABLE IF NOT EXISTS person (
  id                  INTEGER   NOT NULL PRIMARY KEY AUTOINCREMENT,
  title               TEXT          NULL,
  firstname           TEXT          NULL,
  lastname            TEXT          NULL,
  company	      TEXT          NULL,
  street              TEXT          NULL,
  street_no           TEXT          NULL,
  zip_code            TEXT          NULL,
  location            TEXT          NULL,
  birthday            INTEGER       NULL,
  phone_area          TEXT          NULL,
  phone_number        TEXT          NULL,
  mobile_area         TEXT          NULL,
  mobile_number       TEXT          NULL,
  fax_area            TEXT          NULL,
  fax_number          TEXT          NULL,
  mail                TEXT          NULL,
  institution         TEXT          NULL,
  iban                TEXT          NULL,
  bic                 TEXT          NULL,
  notes               TEXT          NULL,
  created_at          INTEGER   NOT NULL DEFAULT (strftime('%s','now')),
  updated_at          INTEGER   NOT NULL DEFAULT 0
)
    )<<";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString path( QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) );
    QDir::root().mkpath(path);

    db.setDatabaseName( path + "/persons.db");
    if( !db.open() ) {
        qDebug() << QString( "Can not open database '%1/repository.db' with error:" ).arg(path) << db.lastError();
        return false;
    }

    qDebug() << QString( "Database '%1/persons.db' opened." ).arg(path);
    QSqlQuery q;
    if( !q.exec( QLatin1String(create_person) ) ) {
        qDebug() << "Can not create person table with error:" << q.lastError();
        return false;
    }

    return true;
}
