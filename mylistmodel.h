#ifndef MYLISTMODEL_H
#define MYLISTMODEL_H


#include <QAbstractListModel>
#include <QModelIndex>

class MainWindow;

class MyListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MyListModel(MainWindow *w, QObject *parent = 0);
    
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const { return 1; }

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    virtual QModelIndex createIndex ( int row, int column, void * ptr = 0 ) const {
        return QAbstractItemModel::createIndex(row, column, ptr);
    }

signals:
    
public slots:

private:
    MainWindow* w; // XXX - not MVC
    
};

#endif // MYLISTMODEL_H
