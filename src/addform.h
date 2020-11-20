#ifndef ADDFORM_H
#define ADDFORM_H

#include <QColorDialog>
#include <QtWidgets>

namespace Ui {
class ColorForm;
}

class ColorForm : public QWidget{
    Q_OBJECT

public:
    explicit ColorForm(QWidget *parent = nullptr);
    ~ColorForm();

private slots:
    void on_pushButton_clicked();
    void on_chooseColorButton_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
signals:

    void sendItems(QString, QVector<QPair<int, int>>, QString);

private:
    Ui::ColorForm *ui;
    QString color;
    QString name;
};

#endif // ADDFORM_H
