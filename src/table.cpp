#include "table.h"

Table::Table( QString name, QVector<QPair<int, int>> items, QString color):
      name(name), items(items), color(color){
    setColumnCount(items.size());
    setRowCount(2);
    setShowGrid(true);
    for(int col = 0; col<items.size(); col++){
        QString xItem = QString::number( items[col].first );
        QString yItem = QString::number( items[col].second );

        QVariant xVariant(xItem);
        QVariant yVariant(yItem);

        QTableWidgetItem * pxItem = new QTableWidgetItem();
        QTableWidgetItem * pyItem = new QTableWidgetItem();

        pxItem->setData( Qt::DisplayRole, xItem );
        pyItem->setData( Qt::DisplayRole, yItem );

        setItem(0, col, pxItem);
        setItem(1, col, pyItem);
    }
}

Table::~Table(){}

