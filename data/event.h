#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QDate>
#include <QTimeZone>

#include "utils.h"

enum TIMER_STATE {
    RUNNING = 'R',
    STOPPED = 'S',
};

TIMER_STATE strToTimerState(const QString &str);
QString timerStateToStr(const TIMER_STATE &ts);

class Event : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId CONSTANT)
    Q_PROPERTY(int taskId READ getTaskId CONSTANT)
    Q_PROPERTY(QDateTime moment READ getMoment CONSTANT)
    Q_PROPERTY(QString state READ getStateString CONSTANT)
    Q_PROPERTY(QString passed READ getPassedTimeSinceStart CONSTANT)
public:
    Event();
    Event(int taskId, const QString moment, const QString state);
    Event(int id, int taskId, const QString moment, const QString state);

    int getId();
    int getTaskId();
    QDateTime getMoment();
    TIMER_STATE getState();
    QString getStateString();
    QString getPassedTimeSinceStart();
private:
    int id;
    int taskId;
    QDateTime moment;
    TIMER_STATE state;
};

#endif // EVENT_H
