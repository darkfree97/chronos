#include "event.h"

Event::Event(){}

Event::Event(int taskId, const QString moment, const QString state)
{
    this->taskId = taskId;
    this->moment = QDateTime::fromString(moment, Qt::ISODate); this->moment.setTimeSpec(Qt::UTC);
    this->moment = this->moment.toTimeZone(QTimeZone::systemTimeZone());
    this->state = strToTimerState(state);
}

Event::Event(int id, int taskId, const QString moment, const QString state) : Event(taskId, moment, state)
{
    this->id = id;
}

int Event::getId()
{
    return this->id;
}

int Event::getTaskId()
{
    return this->taskId;
}

QDateTime Event::getMoment()
{
    return this->moment;
}

TIMER_STATE Event::getState()
{
    return this->state;
}

QString Event::getStateString()
{
    return timerStateToStr(this->state);
}

QString Event::getPassedTimeSinceStart()
{
    if (this->getState() == TIMER_STATE::STOPPED) return "00:00:00";
    int trackedSec = this->getMoment().secsTo(QDateTime::currentDateTime());
    return secsToTime(trackedSec).toString();
}


TIMER_STATE strToTimerState(const QString &str) {
    if (str.compare("R") == 0) {
        return TIMER_STATE::RUNNING;
    }
    return TIMER_STATE::STOPPED;
}

QString timerStateToStr(const TIMER_STATE &ts) {
    if (ts == TIMER_STATE::RUNNING) return "R";
    return "S";
}
