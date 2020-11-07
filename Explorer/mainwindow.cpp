#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QDir dir = QFileDialog::getExistingDirectory(this, tr("Выбрать директорию"));
    ui->setupUi(this);
    setCentralWidget(ui->textBrowser);
    printDir(dir.absolutePath(), 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString getSpaces(int n) {
    QString s("");
    for(int i = 0; i < n; i++)
        s.append(" ");
    return s;
}

void MainWindow::printDir(QString s, int n) {
    QDir d(s);
    QString spaces = getSpaces(n);
    for(QFileInfo t : d.entryInfoList()){
        QString filename = t.fileName();
        if (t.isDir()) {
            if (filename != "." && filename != ".."){
                ui->textBrowser->append(spaces + "\\" + filename);
                printDir(t.absoluteFilePath(), n+2);
            }
        } else if (t.isFile()) {
            ui->textBrowser->append(spaces + filename);
        }
    }
}
