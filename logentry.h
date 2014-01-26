#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <QString>

struct LogEntry {
    double timestamp;
    QString text;
    double y; // for calculations
};

#endif // LOGENTRY_H
