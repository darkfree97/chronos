#include "dbmanager.h"


DBManager::DBManager(QObject *parent) : QObject{parent}
{
    // connect to the database
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName("tracked.sqlite");
    if (!this->db.open()) {
        qDebug() << "Failed to connect to the database.";
        QGuiApplication::quit();
    }

    this->taskManager = new TasksManager(&(this->db), this);
    this->eventsManager = new EventsManager(&(this->db), this);
}

TasksManager *DBManager::tasks()
{
    return this->taskManager;
}

EventsManager *DBManager::events()
{
    return this->eventsManager;
}
