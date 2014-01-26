#ifndef MYITEMSELECTIONMODEL_H
#define MYITEMSELECTIONMODEL_H

#include <QItemSelectionModel>

class MainWindow;

class MyItemSelectionModel : public QItemSelectionModel
{
    Q_OBJECT
public:
    explicit MyItemSelectionModel(MainWindow *w, QAbstractItemModel *parent = 0);
    
signals:
    
protected:
    void emitSelectionChanged(const QItemSelection &newSelection, const QItemSelection &oldSelection);

public slots:

private:
    MainWindow* w; // XXX - not MVC
};

#endif // MYITEMSELECTIONMODEL_H
