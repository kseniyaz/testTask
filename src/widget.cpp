#include "widget.h"
#include "ui_widget.h"

const QString DB_TABLE_NAME = "items";
const QString DB_NAME = "db.sqlite";
const QString DB_DRIVER_TYPE = "QSQLITE";

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    sdb(QSqlDatabase::addDatabase(DB_DRIVER_TYPE)),
    chartView(new QChartView(this))
{
    ui->setupUi(this);
    ui->gridLayout->addWidget(chartView);
    ui->tabWidget->clear();

    sdb.setDatabaseName(DB_NAME);

    if (!sdb.open()) qDebug() << "database do not open";

    if ( sdb.tables().contains( DB_TABLE_NAME )) return;

    auto createTable = QString("CREATE TABLE %1(name text, x int, y int, color text);").arg(DB_TABLE_NAME);
    QSqlQuery query;
    if(!query.exec(createTable)) qDebug() << "\"CREATE TABLE\" error: " << query.lastError();
}

Widget::~Widget(){
    sdb.close();
    delete chartView;
    delete ui;
}

void Widget::on_saveButton_clicked(){
    auto table = currentTable();
    if(!table) return;

    auto name = table->name;
    auto items = table->items;
    auto color = table->color;
    QSqlQuery query;
    auto deleteOldItems = QString("DELETE FROM %1 WHERE name = '%2'").arg(DB_TABLE_NAME).arg(name);
    if(!query.exec(deleteOldItems)) qDebug() << "Unable to delete data"  << query.lastError() << " : " << query.lastQuery();
    else qDebug() << "Data deleted";

    auto insert = QString("INSERT INTO %1(name, x, y, color) VALUES").arg(DB_TABLE_NAME);
    for(auto item: items) insert+= QString("('%1', %2, %3, '%4'),").arg(name).arg(item.first).arg(item.second).arg(color);

    insert.chop(1);
    insert+=";";
    if(!query.exec(insert)) qDebug() << "Unable to insert data"  << query.lastError() << " : " << query.lastQuery();
    else qDebug() << "Data saved";
}

void Widget::render(QString name, QVector<QPair<int, int>> items, QString color){
    QLineSeries *series = new QLineSeries();
    series->setName(name);

    for(auto item: items) *series << QPointF(item.first, item.second);

    QScatterSeries *series0 = new QScatterSeries();

    for(auto item: items) *series0 << QPointF(item.first, item.second);
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(10.0);

    QChart *chart = new QChart();
    series->setColor(color);
    series0->setColor(color);
    chart->addSeries(series);
    chart->addSeries(series0);

    QValueAxis *axisX = new QValueAxis();
    axisX->setTickCount(0);
    chart->addAxis(axisX, Qt::AlignBottom);


    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%g");
    axisY->setTickCount(0);

    QPen axisPen(QRgb(0xd18952));
    axisPen.setWidth(2);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);
    axisX->setLinePenColor(Qt::black);
    axisY->setLinePenColor(Qt::black);

    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chartView->setChart(chart);
}

void Widget::receiveItems(QString name, QVector<QPair<int, int>> items, QString color){
    tableWindow->close();
    delete tableWindow;
    if(items.isEmpty()) return;

    if(name.isEmpty()) name = "default";
    if(color.isEmpty()) color = "#000000";
    auto table = findTabTableByLabel(name);
    if(table) ui->tabWidget->removeTab(ui->tabWidget->indexOf(table));
    addTable(name, items, color);
}

void Widget::addTable(QString name, QVector<QPair<int, int>> items, QString color){
    Table* table = new Table(name, items, color);
    ui->tabWidget->addTab(table, name);
    setCurrentIndexLast();
}

void Widget::setCurrentIndexLast(){
    ui->tabWidget->setCurrentIndex( ui->tabWidget->count() - 1);
}

void Widget::on_LoadButton_clicked(){
    ui->tabWidget->clear();
    QString selectNames = QString("SELECT DISTINCT name FROM %1;").arg(DB_TABLE_NAME);

    QSqlQuery query;
    if(!query.exec(selectNames)) qDebug() << "Unable to select names"  << query.lastError() << " : " << query.lastQuery();
    else qDebug() << "Names selected";

    QVector<QString> names(0);
    while (query.next()) names.push_back(query.value(0).toString());

    for(auto name: names){
        QString selectItems = QString("SELECT * FROM %1 WHERE name = '%2';").arg(DB_TABLE_NAME).arg(name);

        if(!query.exec(selectItems)) qDebug() << "Unable to select items"  << query.lastError() << " : " << query.lastQuery();
        else qDebug() << "Items selected";

        QVector<QPair<int, int>> items;
        QString color;
        while (query.next()) {
            auto x = query.value(1).toInt();
            auto y = query.value(2).toInt();
            color = query.value(3).toString();
            items.push_back(QPair<int, int>(x, y));
        }
        addTable(name, items, color);
    }
}

void Widget::on_DeleteButton_clicked(){
    auto table = currentTable();
    if(!table) return;
    auto name = table->name;
    QSqlQuery query;
    QString deleteItems =  QString("DELETE FROM %1 WHERE name = '%2'").arg(DB_TABLE_NAME).arg(name);
    if(!query.exec(deleteItems)) qDebug() << "Unable to delete data"  << query.lastError() << " : " << query.lastQuery();
    else qDebug()<<"Data deleted";
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}

void Widget::on_addButton_clicked(){
    tableWindow = new ColorForm();
    connect(tableWindow, &ColorForm::sendItems, this, &Widget::receiveItems);
    tableWindow->show();
}

int Widget::currentTableIndex(){
    return ui->tabWidget->currentIndex();
}

Table* Widget::currentTable(){
    if(currentTableIndex()<0)     return nullptr;
    return static_cast<Table*>(ui->tabWidget->currentWidget());
}

Table* Widget::findTabTableByLabel(QString label){
    auto tabCount = ui->tabWidget->count();
    for(int tabIndex = 0; tabIndex < tabCount; tabIndex++)
        if(ui->tabWidget->tabText(tabIndex).compare(label)==0) return static_cast<Table*>(ui->tabWidget->widget(tabIndex));

    return  nullptr;
}

void Widget::renderFromCurrentTable(){
    auto table = currentTable();
    if(!table) return;

    auto name = table->name;
    auto items = table->items;
    auto color = table->color;

    render(name, items, color);
}

void Widget::on_tabWidget_currentChanged(int index){
    if(index>=0) renderFromCurrentTable();
}
