#include <stdio.h>
#include <assert.h>
#include <QApplication>
#include "mainwindow.h"
#include "logentry.h"


int main(int argc, char *argv[])
{
    QVector<LogEntry> *logs = new QVector<LogEntry>();
    logs->reserve(1000);

    const char* fn = "-";
    FILE* f = stdin;

    if(getenv("F")) fn = getenv("F");

    if(QString(fn) != "-") {
        f = fopen(fn, "rt");
        assert(f);
    } else {
        fprintf(stderr, "Reading logs from stdin until EOF\n");
        fprintf(stderr, "Each line must begin with monotonously increasing number (timestamp)\n");
        fflush(stderr);
    }

    for(;;) {
        char buf[2048];
        if(!fgets(buf, sizeof buf, f)) break;

        struct LogEntry le;
        le.text = buf;
        assert(sscanf(buf, "%lf", &le.timestamp)==1);

        logs->append(le);
    }
    fclose(f);

    QApplication a(argc, argv);
    MainWindow w;
    w.setLogData(logs); // xxx: not MVC
    w.init();
    w.show();

    // xxx: "logs" never deleted.
    
    return a.exec();
}
