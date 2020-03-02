#include "mytablemodel.h"


MyTableModel::MyTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

void MyTableModel::registerColumn(AbstractColumn *column)
{
    //adding a column to the list
    m_columns.append(column);

}

void MyTableModel::addRow(QVariantMap rowData)
{
    //the ID is stored in a field with the name "id"
    int id = rowData.value("id").toInt();

    beginInsertRows(QModelIndex(), m_rowIndex.count(), m_rowIndex.count());

    //add to index
    m_rowIndex.append(id);

    //add data to hash
    m_dataHash.insert(id, rowData);
    endInsertRows();

}

int MyTableModel::idRow(int row) const
{
    //getting the id from our index
    return m_rowIndex.at(row);

}

int MyTableModel::colName(QString name) const
{
    for(int i = 0; i < m_columns.count(); ++i){
        if(nameByCol(i) == name){
            return i;
        }
    }
    //return a negative id
    return -1;

}

QString MyTableModel::nameByCol(int col) const
{
    return m_columns.at(col)->name();

}

int MyTableModel::rowCount(const QModelIndex &parent) const
{
    return  m_rowIndex.count();

}

int MyTableModel::columnCount(const QModelIndex &parent) const
{
    return m_columns.count();

}

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }
    else{
        //find the data
        int id = idRow(index.row());

        //getting the row data
        QVariantMap rowData = m_dataHash.value(id);

        return  m_columns.at(index.column())->colData(rowData, role);
    }

}

SimpleColumn::SimpleColumn(QString name) : AbstractColumn(name)
{

}

QVariant SimpleColumn::colData(QVariantMap &rowData, int role)
{
    //we process in the case of Qt::DisplayRole or not
    if(role != Qt::DisplayRole){
        return QVariant();
    }
    else{
        return rowData.value(name());
    }
}



AbstractColumn::AbstractColumn(QString name) : m_name(name)
{

}

//sets the names of rows and columns
QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole){
        return QVariant();
    }

    if(orientation == Qt::Horizontal){

        return QString("PACKET %1").arg(section + 1);
    }
    else{
        switch (section) {

        case 0: return QString("ID");
        case 1: return QString("Time create");
        case 2: return QString("Third sensor");
        case 3: return QString("Fourth sensor");
        case 4: return QString("Fifth sensor");
        case 5: return QString("Sixth sensor");
        case 6: return QString("Seventh sensor");
        case 7: return QString("Eighth sensor");
        case 8: return QString("Ninth sensor");
        case 9: return QString("Tenth sensor");
        case 10: return QString("Eleventh sensor");
        case 11: return QString("Twelfth sensor");

        default: return  QVariant();

        }
       // return QString("Packet header %1").arg(section + 1);
    }
}
