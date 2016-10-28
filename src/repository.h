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

    void purge();

    Q_INVOKABLE int countPersons() const;

    Q_INVOKABLE Person* getPersonAt(int index) const;
    Q_INVOKABLE Person* getPersonById(int id) const;

    Q_INVOKABLE void upsertPerson(Person *p);
    Q_INVOKABLE void addPerson(Person *p);
    Q_INVOKABLE void updatePerson(Person *p);
    Q_INVOKABLE void removePerson(Person *p);

    Q_INVOKABLE bool exportData(const QString &fileName);
    Q_INVOKABLE bool importData(const QString &fileName);

signals:
    void dataChanged();

private:
    bool initDb();
    Person* parsePerson(const QSqlQuery &q) const;
};


#endif
