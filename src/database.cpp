#include "database.h"
#include <QLogValueAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>
#include <QTableView>
#include <math.h>
/*
DataBase::DataBase()
{
        QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
        sdb.setDatabaseName("db1.sqlite");

        if (!sdb.open()) {
                qDebug() << "do not open";
        }


        QSqlQuery query;
        QString create_table = "CREATE TABLE nabor( "
                   "x int, y int, name text, color text);";

        if(!query.exec(create_table))
        {
                qDebug() << "\"CREATE TABLE\" error: " << query.lastError();
        }


        x_values          = new int[10];
        y_values          = new int[10];

        name = "third values";
        color = "0xFFFFFF";
        for(int i=0;i<10;i++){
            x_values[i] = i;
            y_values[i] = i;
        }
        AddData( x_values, y_values, name , color, query);
}

void DataBase::AddData(int * x_values, int * y_values, QString name , QString color,QSqlQuery &query)
{

    QString insert               =   "INSERT INTO nabor(x, y, name, color) VALUES(%1, %2, '%3', '%4');";
    //  query.exec("insert into nabor values(101, 44, 'values', '0xFFFFFF')");
    for(int i=0;i<10;i++){
        if(!query.exec(insert.arg(x_values[i]).arg(y_values[i]).arg(name).arg(color)))
        {
            qDebug() << "Unable to insert data"  << query.lastError() << " : " << query.lastQuery();
        }
    }
}
*/
DataBase::~DataBase()
{

}
