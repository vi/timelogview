#include "mainwindow.h"
#include "mylistmodel.h"

MyListModel::MyListModel(MainWindow *w, QObject *parent) :
    QAbstractListModel(parent),
    w(w)
{

}


int MyListModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return w->logs->size();
}

QVariant MyListModel::data(const QModelIndex &index, int role) const
{
    if (role==Qt::DisplayRole) {
        return (w->logs->at(index.row()).text);
    }
    return QVariant();
}
