#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickView>

#include "repository.h"
#include "person.h"

#include "model.h"
#include "sortfilterproxymodel.h"

#include "ModelTest/modeltest.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("persons");
    QApplication::setApplicationDisplayName("Persons");
    QApplication::setApplicationVersion("0.0.1");

    qmlRegisterType<Person>("persons", 1, 0, "Person");

    Repository *repository = new Repository(&app);

    // clean database
//    repository->purge();

//    if(repository->countPersons() <= 0) {
//        repository->importData(":/data/data.json");
//    }

    bool enableCanFetchMore = true;
    Model *model = new Model(enableCanFetchMore, &app);
    model->setRepository(repository);

    SortFilterProxyModel *proxy = new SortFilterProxyModel(&app);
    proxy->setSourceModel(model);
//    proxy->sort(0);

//    new ModelTest(model, &app);
//    new ModelTest(proxy, &app);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("repository"), repository);
    engine.rootContext()->setContextProperty(QStringLiteral("personModel"), proxy);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
