#include <QApplication>
#include <QDebug>
#include <QFile>
#include "mainwindow.h"

void dummyOutput(QtMsgType type, const QMessageLogContext& context, const QString& message) {}

void messageToFile(QtMsgType type, const QMessageLogContext& context, const QString& message) {
    QFile file("protocol.log");

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        return;
    }

    QTextStream out(&file);
    switch (type) {
        case QtDebugMsg:
            out << "Debug: " << message << ", " << context.file << endl;
            break;
        case QtWarningMsg:
            out << "Warning: " << message << ", " << context.file << endl;
            break;
        case QtCriticalMsg:
            out << "Critical: " << message << ", " << context.file << endl;
            break;
        case QtFatalMsg:
            out << "Fatal: " << message << ", " << context.file << endl;
            abort();
    }

}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QString mode("Standart");

    if (mode == "FileLog") {
        qInstallMessageHandler(messageToFile);
    } else if (mode == "Dummy") {
        qInstallMessageHandler(dummyOutput);
    }

    QObject* ptr1 = new QObject(nullptr);
    QObject* ptr2 = new QObject(ptr1);
    QObject* ptr3 = new QObject(ptr1);
    QObject* ptr4 = new QObject(ptr2);
    ptr1->setObjectName("1");
    ptr2->setObjectName("2");
    ptr3->setObjectName("3");
    ptr4->setObjectName("4");

    for (QObject* ptr = ptr4; ptr; ptr = ptr->parent()) {
        qDebug() << ptr->objectName();
    }

    QList<QObject*> list = ptr1->findChildren<QObject*>();

    for (QObject* tmp : list) {
        qDebug() << tmp;
    }

    qDebug() << "\nObject Dump Info: ";
    ptr1->dumpObjectInfo();
    ptr1->dumpObjectTree();

    qDebug() << "\nObject Class Name:" << ptr2->metaObject()->className();

    // Q_ASSERT(false);
    //QObject* ptr = nullptr;
    //Q_CHECK_PTR(ptr);

    qDebug() << "\nDebug!";
    qWarning() << "Warning!";
    //qFatal("Fatal!");

    qDebug() << qMax(9, qMin(12, 8));
    qDebug() << qAbs(-283);
    qDebug() << qRound(23.8);
    qDebug() << qRound(-23.8);
    qDebug() << qBound(1, 3, 2);

    //page 87

    MainWindow mainWindow(nullptr);
    mainWindow.setWindowFlag(Qt::Window);
    mainWindow.show();

    //page 132

    return app.exec();
}
