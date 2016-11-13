#include "person.h"

#include <QJsonObject>

Person::Person(QObject *parent)
  : QObject(parent)
{
}

Person::Person(const QString &firstName, const QString &lastName, QObject *parent)
  : QObject(parent)
{
    m_firstName = firstName;
    m_lastName = lastName;
}

Person::Person(const QJsonObject &json, QObject *parent)
  : QObject(parent)
{
    bool b = blockSignals(true);

    setId(json.value(QStringLiteral("id")).toInt(-1));
    setTitle(json.value(QStringLiteral("title")).toString());
    setFirstName(json.value(QStringLiteral("first_name")).toString());
    setLastName(json.value(QStringLiteral("last_name")).toString());
    setCompany(json.value(QStringLiteral("company")).toString());
    setStreet(json.value(QStringLiteral("street")).toString());
    setStreetNo(json.value(QStringLiteral("street_no")).toString());
    setZipCode(json.value(QStringLiteral("zip")).toString());
    setLocation(json.value(QStringLiteral("location")).toString());
    setBirthday(QDate::fromString(json.value(QStringLiteral("birthday")).toString(), Qt::ISODate));
    setPhoneArea(QString::number(json.value(QStringLiteral("phone_area")).toInt()));
    setPhoneNumber(QString::number(json.value(QStringLiteral("phone_number")).toInt()));
    setFaxArea(QString::number(json.value(QStringLiteral("fax_area")).toInt()));
    setFaxNumber(QString::number(json.value(QStringLiteral("fax_number")).toInt()));
    setMobileArea(QString::number(json.value(QStringLiteral("mobile_area")).toInt()));
    setMobileNumber(QString::number(json.value(QStringLiteral("mobile_number")).toInt()));
    setMail(json.value(QStringLiteral("mail")).toString());
    setInstitution(json.value(QStringLiteral("institution")).toString());
    setIBAN(json.value(QStringLiteral("iban")).toString());
    setBIC(QString::number(json.value(QStringLiteral("bic")).toInt()));
    setNotes(json.value(QStringLiteral("notes")).toString());
    setCreatedAt(QDateTime::fromString(json.value(QStringLiteral("created_at")).toString(), Qt::ISODate));
    setUpdatedAt(QDateTime::fromString(json.value(QStringLiteral("updated_at")).toString(), Qt::ISODate));

    blockSignals(b);
}

void Person::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged();
}

void Person::setTitle(const QString &title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged();
}

void Person::setFirstName(const QString &firstName)
{
    if (m_firstName == firstName)
        return;

    m_firstName = firstName;
    emit firstNameChanged();
}

void Person::setLastName(const QString &lastName)
{
    if (m_lastName == lastName)
        return;

    m_lastName = lastName;
    emit lastNameChanged();
}

void Person::setCompany(const QString &company)
{
    if (m_company == company)
        return;

    m_company = company;
    emit companyChanged();
}

void Person::setStreet(const QString &street)
{
    if (m_street == street)
        return;

    m_street = street;
    emit streetChanged();
}

void Person::setStreetNo(const QString &streetNo)
{
    if (m_streetNo == streetNo)
        return;

    m_streetNo = streetNo;
    emit streetNoChanged();
}

void Person::setZipCode(const QString &zipCode)
{
    if (m_zipCode == zipCode)
        return;

    m_zipCode = zipCode;
    emit zipCodeChanged();
}

void Person::setLocation(const QString &location)
{
    if (m_location == location)
        return;

    m_location = location;
    emit locationChanged();
}

void Person::setBirthday(QDate birthday)
{
    if (m_birthday == birthday)
        return;

    m_birthday = birthday;
    emit birthdayChanged();
}

void Person::setPhoneArea(const QString &phoneArea)
{
    if (m_phoneArea == phoneArea)
        return;

    m_phoneArea = phoneArea;
    emit phoneAreaChanged();
}

void Person::setPhoneNumber(const QString &phoneNumber)
{
    if (m_phoneNumber == phoneNumber)
        return;

    m_phoneNumber = phoneNumber;
    emit phoneNumberChanged();
}

void Person::setFaxArea(const QString &faxArea)
{
    if (m_faxArea == faxArea)
        return;

    m_faxArea = faxArea;
    emit faxAreaChanged();
}

void Person::setFaxNumber(const QString &faxNumber)
{
    if (m_faxNumber == faxNumber)
        return;

    m_faxNumber = faxNumber;
    emit faxNumberChanged();
}

void Person::setMobileArea(const QString &mobileArea)
{
    if (m_mobileArea == mobileArea)
        return;

    m_mobileArea = mobileArea;
    emit mobileAreaChanged();
}

void Person::setMobileNumber(const QString &mobileNumber)
{
    if (m_mobileNumber == mobileNumber)
        return;

    m_mobileNumber = mobileNumber;
    emit mobileNumberChanged();
}

void Person::setMail(const QString &mail)
{
    if (m_mail == mail)
        return;

    m_mail = mail;
    emit mailChanged();
}

void Person::setInstitution(const QString &institution)
{
    if (m_institution == institution)
        return;

    m_institution = institution;
    emit institutionChanged();
}

void Person::setIBAN(const QString &IBAN)
{
    if (m_IBAN == IBAN)
        return;

    m_IBAN = IBAN;
    emit IBANChanged();
}

void Person::setBIC(const QString &BIC)
{
    if (m_BIC == BIC)
        return;

    m_BIC = BIC;
    emit BICChanged();
}

void Person::setNotes(const QString &notes)
{
    if (m_notes == notes)
        return;

    m_notes = notes;
    emit notesChanged();
}

void Person::setCreatedAt(const QDateTime &createdAt)
{
    if (m_createdAt == createdAt)
        return;

    m_createdAt = createdAt;
    emit createdAtChanged();
}

void Person::setUpdatedAt(const QDateTime &updatedAt)
{
    if (m_updatedAt == updatedAt)
        return;

    m_updatedAt = updatedAt;
    emit updatedAtChanged();
}

QJsonObject Person::toJson() const
{
    QJsonObject obj;
    obj.insert(QStringLiteral("id"), id());
    obj.insert(QStringLiteral("title"), title());
    obj.insert(QStringLiteral("first_name"), firstName());
    obj.insert(QStringLiteral("last_name"), lastName());
    obj.insert(QStringLiteral("company"), company());
    obj.insert(QStringLiteral("street"), street());
    obj.insert(QStringLiteral("street_no"), streetNo());
    obj.insert(QStringLiteral("zip"), zipCode());
    obj.insert(QStringLiteral("location"), location());
    obj.insert(QStringLiteral("birthday"), birthday().toString(Qt::ISODate));
    obj.insert(QStringLiteral("phone_area"), phoneArea());
    obj.insert(QStringLiteral("phone_number"), phoneNumber());
    obj.insert(QStringLiteral("fax_area"), faxArea());
    obj.insert(QStringLiteral("fax_number"), faxNumber());
    obj.insert(QStringLiteral("mobile_area"), mobileArea());
    obj.insert(QStringLiteral("mobile_number"), mobileNumber());
    obj.insert(QStringLiteral("mail"), mail());
    obj.insert(QStringLiteral("institution"), institution());
    obj.insert(QStringLiteral("iban"), IBAN());
    obj.insert(QStringLiteral("bic"), BIC());
    obj.insert(QStringLiteral("notes"), notes());
    obj.insert(QStringLiteral("created_at"), createdAt().toString(Qt::ISODate));
    obj.insert(QStringLiteral("updated_at"), updatedAt().toString(Qt::ISODate));

    return obj;
}
