#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>

class Table : public QTableWidget{
    Q_OBJECT

public:
    explicit Table(QString, QVector<QPair<int, int>>, QString);
    ~Table();

    QString name;
    QVector<QPair<int, int>> items;
    QString color;
};

#endif // ADDFORM_H
