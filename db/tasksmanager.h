#ifndef TASKSMANAGER_H
#define TASKSMANAGER_H

#include <QGuiApplication>
#include <QObject>
#include <QtSql>
#include <QList>

#include "data/task.h"

class TasksManager : public QObject
{
    Q_OBJECT
public:
    TasksManager(QSqlDatabase *db, QObject *parent = nullptr);

    void createTask(Task &task);
    void updateTask(Task &task);
    QList<Task *> retrieveTasks();
private:
    QSqlDatabase *db;
    QList<Task *> tasks;
};

#endif // TASKSMANAGER_H
