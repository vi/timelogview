#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logentry.h"
#include <QVector>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QModelIndex;
class QCPAbstractPlottable;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class MyListModel;
    friend class MyItemSelectionModel;
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void setLogData(QVector<struct LogEntry> *l) { logs = l; }
    void init();
    ~MainWindow();
    
private slots:
    void	currentChanged ( const QModelIndex & current, const QModelIndex & previous );
    void    plottableClick(QCPAbstractPlottable *plottable, QMouseEvent *event);
    void    selectionChangedByUser();

private:
    void setupGraph();
    void setupList();
    QVector<struct LogEntry> *logs;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
