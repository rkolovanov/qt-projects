#include "mainwindow.h"
#include "myqobjectclass.h"
#include <QApplication>
#include <QDebug>


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    MyQObjectClass obj(nullptr);
    qDebug() << obj.property("value").toBool();



    return a.exec();
}
