#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "matrix.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    N::Matrix<int> matrix(3, 3);
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 3;
    matrix[1][0] = 4;
    matrix[1][1] = 5;
    matrix[1][2] = 6;
    matrix[2][0] = 7;
    matrix[2][1] = 8;
    matrix[2][2] = 9;

    for (N::Size i = 0; i < 3; i++) {
        qDebug() << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2];
    }

    return app.exec();
}
