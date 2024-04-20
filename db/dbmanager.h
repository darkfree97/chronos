#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>
#include <QMessageBox>
#include <QGuiApplication>

#include "db/tasksmanager.h"
#include "db/eventsmanager.h"

class DBManager : public QObject
{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = nullptr);

    TasksManager *tasks();
    EventsManager *events();
private:
    QSqlDatabase db;
    TasksManager *taskManager;
    EventsManager *eventsManager;
};

#endif // DBMANAGER_H
