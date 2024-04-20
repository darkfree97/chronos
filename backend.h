#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QList>
#include <qqml.h>

#include "utils.h"
#include "data/task.h"
#include "data/event.h"
#include "db/dbmanager.h"

class Backend : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(void stateChanged NOTIFY stateChanged)
//    Q_PROPERTY(void tasksUpdated NOTIFY tasksUpdated)
    QML_ELEMENT
public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();

signals:
    void stateChanged();
    void tasksUpdated();

public slots:
    void triggerTaskTimer(int taskId);
    void createTask(QString title, QString comments);
    void updateTask(int id, QString title, QString comments);
    QList<Task *> loadTasks();
    Event* loadLastEvent();

private:
    DBManager *db;
};

#endif // BACKEND_H
