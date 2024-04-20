#ifndef TASK_H
#define TASK_H

#include <QObject>

#include "utils.h"

class Task: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId CONSTANT)
    Q_PROPERTY(QString title READ getTitle CONSTANT)
    Q_PROPERTY(QString comments READ getComments CONSTANT)
    Q_PROPERTY(QString trackedTime READ getTrackedTime CONSTANT)
public:
    Task(QObject *parent = nullptr);
    Task(int id, QString title, QString comments, int trackedTime, QObject *parent = nullptr);

    int getId();
    void setId(int id);
    QString getTitle();
    QString getComments();
    QString getTrackedTime();
private:
    int  id;
    QString title;
    QString comments;
    int trackedTime;
};

#endif // TASK_H
