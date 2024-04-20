#include "dbtimerevent.h"
#include <QTimeZone>

DBTimerEvent::DBTimerEvent(){}


DBTimerEvent::DBTimerEvent(const QString moment, const QString state){
    this->moment = QDateTime::fromString(moment, Qt::ISODate); this->moment.setTimeSpec(Qt::UTC);
    this->moment = this->moment.toTimeZone(QTimeZone::systemTimeZone());
    this->state = strToTimerState(state);
}

QDateTime DBTimerEvent::getMoment()
{
    return this->moment;
}

TIMER_STATE DBTimerEvent::getState()
{
    return this->state;
}
