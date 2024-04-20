#include "tasksmanager.h"


TasksManager::TasksManager(QSqlDatabase *db, QObject *parent) :  QObject{parent}
{
    this->db = db;

    // initialize database and create tables
    QSqlQuery queryCtx(*this->db);
    QString createTasksTableQuery = ""
    "CREATE TABLE IF NOT EXISTS tasks ("
         "id integer not null constraint task_pk primary key autoincrement, "
         "title varchar(128), "
         "comments varchar(512)"
    ")";
    if (!queryCtx.exec(createTasksTableQuery)) {
        qDebug() << queryCtx.lastError();
        QGuiApplication::quit();
    }

    queryCtx.finish();
}

void TasksManager::createTask(Task &task)
{
    QSqlQuery queryCtx(*this->db);
    QString insertQuery = "INSERT INTO tasks (title, comments, tracked_time) VALUES ('%1', '%2', '%3') RETURNING *;";

    if (!queryCtx.exec(insertQuery.arg(task.getTitle(), task.getComments(), ""))) {
        qDebug() << queryCtx.lastError();
        QGuiApplication::quit();
    }
    queryCtx.finish();
}

void TasksManager::updateTask(Task &task)
{
    QSqlQuery queryCtx(*this->db);
    QString insertQuery = "UPDATE tasks SET title='%1', comments='%2' WHERE id=%3;";

    if (!queryCtx.exec(insertQuery.arg(task.getTitle()).arg(task.getComments()).arg(task.getId()))) {
        qDebug() << queryCtx.lastError();
        QGuiApplication::quit();
    }
    queryCtx.finish();
}

QList<Task *> TasksManager::retrieveTasks()
{
    // Clear previous tasks
    if(!this->tasks.empty()) {
        for (Task *task : this->tasks) {
            delete task;
        }
        this->tasks.clear();
    }

    QSqlQuery queryCtx(*this->db);
    QString selectQuery = ""
    "SELECT "
        "tasks.id, "
        "tasks.title, "
        "tasks.comments, "
        "tracks.tracked "
    "FROM tasks LEFT JOIN ("
        "SELECT "
            "stops.task_id, "
            "SUM(CAST(strftime('%s', stops.moment) as integer) - CAST(strftime('%s', starts.moment) as integer)) as tracked "
        "FROM events stops INNER JOIN events starts ON stops.start_id = starts.id "
        "GROUP BY stops.task_id"
    ") tracks ON tasks.id = tracks.task_id;";
    if (!queryCtx.exec(selectQuery)) {
        qDebug() << queryCtx.lastError();
        QGuiApplication::quit();
    }

    QSqlRecord rec = queryCtx.record();
    while (queryCtx.next()) {
        this->tasks.append(new Task(
            queryCtx.value(rec.indexOf("id")).toInt(),
            queryCtx.value(rec.indexOf("title")).toString(),
            queryCtx.value(rec.indexOf("comments")).toString(),
            queryCtx.value(rec.indexOf("tracked")).toInt(),
            this
        ));
    }
    return this->tasks;
}
