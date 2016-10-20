#ifndef PERSON_H
#define PERSON_H

#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QObject>

class QJsonObject;


class Person : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString company READ company WRITE setCompany NOTIFY companyChanged)
    Q_PROPERTY(QString street READ street WRITE setStreet NOTIFY streetChanged)
    Q_PROPERTY(QString streetNo READ streetNo WRITE setStreetNo NOTIFY streetNoChanged)
    Q_PROPERTY(QString zipCode READ zipCode WRITE setZipCode NOTIFY zipCodeChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QDate birthday READ birthday WRITE setBirthday NOTIFY birthdayChanged)
    Q_PROPERTY(QString phoneArea READ phoneArea WRITE setPhoneArea NOTIFY phoneAreaChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QString faxArea READ faxArea WRITE setFaxArea NOTIFY faxAreaChanged)
    Q_PROPERTY(QString faxNumber READ faxNumber WRITE setFaxNumber NOTIFY faxNumberChanged)
    Q_PROPERTY(QString mobileArea READ mobileArea WRITE setMobileArea NOTIFY mobileAreaChanged)
    Q_PROPERTY(QString mobileNumber READ mobileNumber WRITE setMobileNumber NOTIFY mobileNumberChanged)
    Q_PROPERTY(QString mail READ mail WRITE setMail NOTIFY mailChanged)
    Q_PROPERTY(QString institution READ institution WRITE setInstitution NOTIFY institutionChanged)
    Q_PROPERTY(QString IBAN READ IBAN WRITE setIBAN NOTIFY IBANChanged)
    Q_PROPERTY(QString BIC READ BIC WRITE setBIC NOTIFY BICChanged)
    Q_PROPERTY(QString notes READ notes WRITE setNotes NOTIFY notesChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)

    public:
        Q_INVOKABLE explicit Person(QObject *parent = nullptr);

        explicit Person(const QString &firstName, const QString &lastName, QObject *parent = nullptr);
        explicit Person(const QJsonObject &json, QObject *parent = nullptr);


        Q_INVOKABLE bool isEmpty() const
        {
            return m_firstName.isEmpty() && m_lastName.isEmpty() && m_company.isEmpty();
        }

        int id() const
        {
            return m_id;
        }

        QString title() const
        {
            return m_title;
        }

        QString firstName() const
        {
            return m_firstName;
        }

        QString lastName() const
        {
            return m_lastName;
        }

        QString company() const
        {
            return m_company;
        }

        QString street() const
        {
            return m_street;
        }

        QString streetNo() const
        {
            return m_streetNo;
        }

        QString zipCode() const
        {
            return m_zipCode;
        }

        QString location() const
        {
            return m_location;
        }

        QDate birthday() const
        {
            return m_birthday;
        }

        QString phoneArea() const
        {
            return m_phoneArea;
        }

        QString phoneNumber() const
        {
            return m_phoneNumber;
        }

        QString faxArea() const
        {
            return m_faxArea;
        }

        QString faxNumber() const
        {
            return m_faxNumber;
        }

        QString mobileArea() const
        {
            return m_mobileArea;
        }

        QString mobileNumber() const
        {
            return m_mobileNumber;
        }

        QString mail() const
        {
            return m_mail;
        }

        QString institution() const
        {
            return m_institution;
        }

        QString IBAN() const
        {
            return m_IBAN;
        }

        QString BIC() const
        {
            return m_BIC;
        }

        QString notes() const
        {
            return m_notes;
        }

        QDateTime createdAt() const
        {
            return m_createdAt;
        }

        QDateTime updatedAt() const
        {
            return m_updatedAt;
        }


        QJsonObject toJson() const;

    public slots:
        void setId(int id);
        void setTitle(const QString &title);
        void setFirstName(const QString &firstName);
        void setLastName(const QString &lastName);
        void setCompany(const QString &company);
        void setStreet(const QString &street);
        void setStreetNo(const QString &streetNo);
        void setZipCode(const QString &zipCode);
        void setLocation(const QString &location);
        void setBirthday(QDate birthday);
        void setPhoneArea(const QString &phoneArea);
        void setPhoneNumber(const QString &phoneNumber);
        void setFaxArea(const QString &faxArea);
        void setFaxNumber(const QString &faxNumber);
        void setMobileArea(const QString &mobileArea);
        void setMobileNumber(const QString &mobileNumber);
        void setMail(const QString &mail);
        void setInstitution(const QString &institution);
        void setIBAN(const QString &IBAN);
        void setBIC(const QString &BIC);
        void setNotes(const QString &notes);
        void setCreatedAt(const QDateTime &createdAt);
        void setUpdatedAt(const QDateTime &updatedAt);

    signals:
        void idChanged();
        void titleChanged();
        void firstNameChanged();
        void lastNameChanged();
        void companyChanged();
        void streetChanged();
        void streetNoChanged();
        void zipCodeChanged();
        void locationChanged();
        void birthdayChanged();
        void phoneAreaChanged();
        void phoneNumberChanged();
        void faxAreaChanged();
        void faxNumberChanged();
        void mobileAreaChanged();
        void mobileNumberChanged();
        void mailChanged();
        void institutionChanged();
        void IBANChanged();
        void BICChanged();
        void notesChanged();
        void createdAtChanged();
        void updatedAtChanged();

    private:
        int m_id = -1;
        QString m_title;
        QString m_firstName;
        QString m_lastName;
        QString m_company;
        QString m_street;
        QString m_streetNo;
        QString m_zipCode;
        QString m_location;
        QDate m_birthday;
        QString m_phoneArea;
        QString m_phoneNumber;
        QString m_faxArea;
        QString m_faxNumber;
        QString m_mobileArea;
        QString m_mobileNumber;
        QString m_mail;
        QString m_institution;
        QString m_IBAN;
        QString m_BIC;
        QString m_notes;
        QDateTime m_createdAt;
        QDateTime m_updatedAt;
};


#endif
