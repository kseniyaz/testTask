#include "addform.h"
#include "widget.h"
#include "ui_addform.h"

ColorForm::ColorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorForm)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(100);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels({"x","y"});
    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
        for(int column = 0; column < ui->tableWidget->columnCount(); column++)
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());

    for(int row=0; row!=ui->tableWidget->rowCount(); row++)
        for(int column=0; column!=ui->tableWidget->columnCount(); column++) {
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(("")));
            ui->tableWidget->setItem(row, column, newItem);
        }

    ui->tableWidget->resizeColumnsToContents();
}

ColorForm::~ColorForm(){
    delete ui;
}

void ColorForm::on_chooseColorButton_clicked(){
    QColorDialog *dialog = new QColorDialog(this);
    dialog->show();
    QObject::connect(dialog,&QDialog::accepted,[=](){
           color = QVariant(dialog->currentColor()).toString();
    });
}

void ColorForm::on_lineEdit_textChanged(const QString &arg1){
    name = arg1;
}

void ColorForm::on_pushButton_clicked(){
    QVector<QPair<int, int>> items(0);

    QVector<int> x(0), y(0);
    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
        if(!(ui->tableWidget->item(row, 0)->text() == "") && !(ui->tableWidget->item(row, 1)->text() == ""))
            items.push_back(QPair<int, int>(ui->tableWidget->item(row, 0)->text().toInt(), ui->tableWidget->item(row, 1)->text().toInt()));

    emit this->sendItems(name, items, color);
}
