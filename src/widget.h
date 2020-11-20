#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtCharts>

#include "table.h"
#include "addform.h"

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

private:
    Ui::Widget *ui;
    ColorForm *tableWindow;
    QSqlDatabase sdb;
    QChartView *chartView;

    void render(QString, QVector<QPair<int, int>>, QString);
    int currentTableIndex();
    void renderFromCurrentTable();
    Table* currentTable();
    void addTable(QString, QVector<QPair<int, int>>, QString);
    Table* findTabTableByLabel(QString);
    void deleteTableByIndex(int index);
    void setCurrentIndexLast();
public:
    Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void receiveItems(QString, QVector<QPair<int, int>>, QString);
    void on_saveButton_clicked();
    void on_LoadButton_clicked();
    void on_DeleteButton_clicked();
    void on_addButton_clicked();
    void on_tabWidget_currentChanged(int);
};
#endif // WIDGET_H
