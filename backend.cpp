#include "backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
{
    this->db = new DBManager(this);
}

Backend::~Backend()
{
    if(this->db != nullptr) delete this->db;
}

void Backend::triggerTaskTimer(int taskId)
{
    Event *lastEvent = this->db->events()->getLastEvent();
    if(lastEvent != nullptr && lastEvent->getState() == TIMER_STATE::RUNNING) {
        this->db->events()->stopTimer(lastEvent->getTaskId(), lastEvent->getId());
        if (lastEvent->getTaskId() != taskId) {
            this->db->events()->startTimer(taskId);
        }
    } else if (lastEvent == nullptr || lastEvent->getState() == TIMER_STATE::STOPPED) {
        this->db->events()->startTimer(taskId);
    }

    this->db->events()->getLastEvent(false);
    emit this->stateChanged();
}

void Backend::createTask(QString title, QString comments)
{
    Task task(0, title, comments, 0);
    this->db->tasks()->createTask(task);
    emit this->tasksUpdated();
}

void Backend::updateTask(int id, QString title, QString comments)
{
    Task task(id, title, comments, 0);
    this->db->tasks()->updateTask(task);
    emit this->tasksUpdated();
}

void Backend::deleteTask(int id)
{
    this->db->tasks()->deleteTask(id);
    this->db->events()->deleteEvents(id);
    emit this->tasksUpdated();
}

QList<Task *> Backend::loadTasks()
{
    return this->db->tasks()->retrieveTasks();
}

Event *Backend::loadLastEvent()
{
    return this->db->events()->getLastEvent();
}
