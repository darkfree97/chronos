#include "utils.h"


QTime secsToTime(int secs)
{
    int mins = secs / 60;
    int hours = mins / 60;
    secs %= 60;
    mins %= 60;
    return QTime(hours, mins, secs);
}
