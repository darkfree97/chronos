#include "eventsmanager.h"

EventsManager::EventsManager(QSqlDatabase *db, QObject *parent) :  QObject{parent}
{
    this->db = db;
    this->lastEvent = nullptr;

    // initialize database and create tables
    QSqlQuery queryCtx(*this->db);
    QString createTasksTableQuery = ""
    "CREATE TABLE IF NOT EXISTS events ("
         "id integer not null constraint event_pk primary key autoincrement, "
         "task_id integer not null, "
         "start_id integer null, "
         "moment timestamp default CURRENT_TIMESTAMP, "
         "type varchar(1) default 'R', "
         "FOREIGN KEY(task_id) REFERENCES tasks(id), "
         "FOREIGN KEY(start_id) REFERENCES events(id)"
    ")";
    if (!queryCtx.exec(createTasksTableQuery)) {
        qDebug() << queryCtx.lastError();
        QGuiApplication::quit();
    }

    queryCtx.finish();
}

void EventsManager::startTimer(int taskId)
{
    QSqlQuery queryCtx(*this->db);
    QString insertQuery = "INSERT INTO events (task_id, type) VALUES (%1, 'R');";
    Event *lastEvent = this->getLastEvent(false);
    if (lastEvent == nullptr || lastEvent->getState() == TIMER_STATE::STOPPED) {

        if (!queryCtx.exec(insertQuery.arg(taskId))) {
            qDebug() << queryCtx.lastError();
            QGuiApplication::quit();
        }
    }
    queryCtx.finish();
}

void EventsManager::stopTimer(int taskId, int startId)
{
    QSqlQuery queryCtx(*this->db);
    QString insertQuery = "INSERT INTO events (task_id, start_id, type) VALUES (%1, %2, 'S');";
    Event *lastEvent = this->getLastEvent();
    if (lastEvent != nullptr && lastEvent->getState() == TIMER_STATE::RUNNING) {
        if (!queryCtx.exec(insertQuery.arg(taskId).arg(startId))) {
            qDebug() << queryCtx.lastError();
            QGuiApplication::quit();
        }
    }
    queryCtx.finish();
}

Event *EventsManager::getLastEvent(bool cached)
{
    bool eventIsNull = this->lastEvent == nullptr;
    if (cached && !eventIsNull) {
        return this->lastEvent;
    }

    if (!eventIsNull) {
        delete this->lastEvent;
        this->lastEvent = nullptr;
    }

    QSqlQuery queryCtx(*this->db);
    QString selectQuery = "SELECT * FROM events ORDER BY id DESC LIMIT 1;";
    if (!queryCtx.exec(selectQuery)) {
        qDebug() << queryCtx.lastError();
        QGuiApplication::quit();
    }

    QSqlRecord rec = queryCtx.record();
    while (queryCtx.next()) {
        this->lastEvent = new Event(
            queryCtx.value(rec.indexOf("id")).toInt(),
            queryCtx.value(rec.indexOf("task_id")).toInt(),
            queryCtx.value(rec.indexOf("moment")).toString(),
            queryCtx.value(rec.indexOf("type")).toString()
        );
        return this->lastEvent;
    }
    queryCtx.finish();
    return this->lastEvent;
}

void EventsManager::deleteEvents(int taskId)
{
    QSqlQuery queryCtx(*this->db);
    QString deleteQuery = "DELETE FROM events WHERE task_id='%1'";

    if (!queryCtx.exec(deleteQuery.arg(taskId))) {
        qDebug() << queryCtx.lastError();
        QGuiApplication::quit();
    }
    queryCtx.finish();
}
