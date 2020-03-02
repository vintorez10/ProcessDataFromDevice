#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QHash>
#include <QString>
#include <QLocale>
#include <QObject>

//Abstract base column class
class AbstractColumn
{
public:
    AbstractColumn(QString name);
    //virtual ~AbstractColumn();
    QString name() {return  m_name;}
    virtual QVariant colData(QVariantMap & rowData, int role = Qt::DisplayRole) = 0;

private:
    QString m_name;

};

class SimpleColumn : public AbstractColumn
{
public:
    SimpleColumn(QString name);

    // AbstractColumn interface
public:
    virtual QVariant colData(QVariantMap &rowData, int role);
};

//the class was created to display data in a table view
//It inherits from an abstract class "QAbstractTableModel"
class MyTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MyTableModel(QObject * parent = nullptr);
    void registerColumn(AbstractColumn* column);
    void addRow(QVariantMap rowData);

    //getting an ID by line number
    int idRow(int row) const;

    //getting the column index by name
    int colName(QString name) const;

    //getting the column name by index
    QString nameByCol(int col) const;

    //~MyTableModel();

private:
    //the index ID is numeric
    QList<int> m_rowIndex;

    QHash<int, QVariantMap> m_dataHash;

    //list of column names
    QList <AbstractColumn*> m_columns;


protected:
    //storing cell data
    //QHash<QModelIndex, QVariant> cellData;


    // QAbstractItemModel interface
public:
    //three mandatory virtual methods have been redefined "rowCount","columnCount","data"
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    //to display header data, the method "headerData" was redefined
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

};

#endif // MYTABLEMODEL_H
