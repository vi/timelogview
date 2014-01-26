#include <stdio.h>

#include "myitemselectionmodel.h"

MyItemSelectionModel::MyItemSelectionModel(MainWindow *w, QAbstractItemModel *parent) :
    QItemSelectionModel(parent),
    w(w)
{
}



void MyItemSelectionModel::emitSelectionChanged(const QItemSelection &newSelection, const QItemSelection &oldSelection)
{
    fprintf(stderr, "Select\n");
    QItemSelectionModel::emitSelectionChanged(newSelection, oldSelection);
}
