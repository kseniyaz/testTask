#include "widget.h"
#include "addform.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Widget w;
    w.setFixedSize(583,532);
    w.show();
    return a.exec();
}
