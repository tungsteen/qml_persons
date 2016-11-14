#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>


class QSqlQuery;
class Person;

class Repository : public QObject
{
    Q_OBJECT

public:
    explicit Repository(QObject *parent = nullptr);

    Q_INVOKABLE void purge();

    Q_INVOKABLE int countPersons() const;

    Q_INVOKABLE Person* getPersonAt(int index) const;
    Q_INVOKABLE Person* getPersonById(int id) const;

    Q_INVOKABLE void upsertPerson(Person *p);
    Q_INVOKABLE void addPerson(Person *p);
    Q_INVOKABLE void updatePerson(const Person *p);
    Q_INVOKABLE void removePerson(const Person *p);

    Q_INVOKABLE bool exportData(const QString &fileName);
    Q_INVOKABLE void importData(const QUrl &fileUrl);
    Q_INVOKABLE bool importData(const QString &fileName);
    Q_INVOKABLE void exportData(const QUrl &fileUrl);

    Q_INVOKABLE void removePersonById(int id);
signals:
    void dataChanged();

private:
    bool initDb();
    Person* parsePerson(const QSqlQuery &q) const;
};


#endif
