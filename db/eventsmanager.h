#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include <QGuiApplication>
#include <QObject>
#include <QtSql>
#include <QTime>

#include "utils.h"
#include "data/event.h"


class EventsManager : public QObject
{
    Q_OBJECT
public:
    EventsManager(QSqlDatabase *db, QObject *parent = nullptr);

    void startTimer(int taskId);
    void stopTimer(int taskId, int startId);
    Event *getLastEvent(bool cached = true);
private:
    QSqlDatabase *db;
    Event *lastEvent;

    QTime getDailyStats(const QDate &start = QDate::currentDate(), QVector<int> *processedIDs = nullptr);
    void squashPreviousDailyStats();
    void deleteRecords(QVector<int> *recordsIDs = nullptr);
    void createStatsRec(const QDate &start = QDate::currentDate(), const QString &trackedTime = "");
};

#endif // EVENTSMANAGER_H
