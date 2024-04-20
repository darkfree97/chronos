#include "task.h"

Task::Task(QObject *parent) : QObject{parent}{}

Task::Task(int id, QString title, QString comments, int trackedTime, QObject *parent) : QObject{parent}
{
    this->id = id;
    this->title = title;
    this->comments = comments;
    this->trackedTime = trackedTime;
}

int Task::getId()
{
    return this->id;
}

void Task::setId(int id)
{
    this->id = id;
}

QString Task::getTitle()
{
    return this->title;
}

QString Task::getComments()
{
    return this->comments;
}

QString Task::getTrackedTime()
{
    return secsToTime(this->trackedTime).toString();
}
