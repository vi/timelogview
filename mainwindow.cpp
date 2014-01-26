#include <assert.h>
#include <QModelIndex>
#include "mainwindow.h"
#include "qcustomplot.h"
#include "mylistmodel.h"
#include "myitemselectionmodel.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    logs(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);
    ui->plot->setInteraction(QCP::iSelectPlottables, true);
    ui->plot->axisRect(0)->setRangeDrag(Qt::Horizontal);
    ui->plot->axisRect(0)->setRangeZoom(Qt::Horizontal);

    ui->plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->plot->xAxis->setSelectableParts(QCPAxis::spNone);

    connect(ui->plot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)),
            this, SLOT(plottableClick(QCPAbstractPlottable*,QMouseEvent*)));
    connect(ui->plot, SIGNAL(selectionChangedByUser()),
            this, SLOT(selectionChangedByUser()));
}


void MainWindow::setupGraph() {
    assert(logs);

    assert(this->logs->size()>0);

    QVector<LogEntry> &l = *this->logs;

    double t = l.at(0).timestamp;
    foreach (LogEntry i, l) {
        assert(i.timestamp >= t || !"timestamp must monotonously increase");
        t = i.timestamp;
        i.y = 0;
    }

    int n = l.size();
    int j;
    t = NAN;
    int count=0; // in this second
    long long int this_second = floor(l.at(0).timestamp);
    for (j=0; j<n; ++j) {
        long long int second = floor(l[j].timestamp);
        fprintf(stderr, "j=%d s=%lld delta=%lld\n", j, second, second-this_second);
        if(second == this_second) {
            ++count;
        } else {
            // go back and assign "count" to count entries.
            int u;
            for(u=1; u<=count; ++u) {
                fprintf(stderr, "Assigned %d to l[%d]\n", count, j-u);
                l[j-u].y = count;
            }
            count=1;
            this_second = second;
        }
    }
    fprintf(stderr, "...\n", j);
    {
        int u;
        for(u=1; u<=count; ++u) {
            fprintf(stderr, "Assigned %d to l[%d]\n", count, j-u);
            l[j-u].y = count;
        }
    }

    //QCPGraph* g = ui->plot->addGraph();
    fprintf(stderr, "init\n");
    for (j=0; j<n; ++j) {
        const LogEntry &i = l[j];

        //fprintf(stderr,"Adding log entry with ts=%lf y=%lf\n", i.timestamp, i.y);
        QCPBars *g = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
        double width = 1.0 / (0.000001 + i.y);
        fprintf(stderr, "%d w=%lf\n", j, width);
        g->setWidth(width);

        g->setProperty("index", j);

        g->addData(i.timestamp, i.y);
        ui->plot->addPlottable(g);
    }

    ui->plot->rescaleAxes();

    ui->plot->replot();
}

void MainWindow::setupList() {
    ui->listView->setModel(new MyListModel(this, this));
    connect(ui->listView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentChanged(QModelIndex,QModelIndex)));
    //ui->listView->setSelectionModel(new MyItemSelectionModel(this, ui->listView->model()));
}

void MainWindow::init() {
    setupGraph();
    setupList();
}


void MainWindow::currentChanged ( const QModelIndex & current, const QModelIndex & previous) {
    (void)previous;
    int i = current.row();
    ui->plainTextEdit->setPlainText(this->logs->at(i).text);

    foreach( QCPAbstractPlottable *p, ui->plot->xAxis->plottables()) {
        p->setSelected(false);
    }

    QCPAbstractPlottable *p = ui->plot->plottable(i);
    if(p) {
        fprintf(stderr, "p %p\n", p);
        p->setSelected(true);
    } else {
        fprintf(stderr, "No p?\n");
    }
    // how to scroll QCustomGraph to the selected item?
    ui->plot->replot();
}

void MainWindow::plottableClick(QCPAbstractPlottable *plottable, QMouseEvent *event)
{
    fprintf(stderr, "plottableClick %p\n", plottable);

}

void MainWindow::selectionChangedByUser()
{
    fprintf(stderr, "selectionChangedByUser\n");

    int i = -1;

    foreach( QCPAbstractPlottable *p, ui->plot->xAxis->plottables()) {
        if (p->selected()) i = p->property("index").toInt();
    }

    if (i!=-1) {

        // Don't know how to just select n'th row without hackery

        MyListModel *m = dynamic_cast<MyListModel*>(ui->listView->model());
        assert(m);
        QModelIndex mi = m->createIndex(i,0,0);
        ui->listView->selectionModel()->select(mi, QItemSelectionModel::ClearAndSelect);
        ui->listView->scrollTo(mi);


        ui->plainTextEdit->setPlainText(this->logs->at(i).text);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
