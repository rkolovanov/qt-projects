#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
#include "fileexplorer.h"


namespace Ui {
    class MainWindow;
}

class MainWindow: public QMainWindow { Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openFile(QString);
    void saveFile(QString);

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionClose_triggered();

                                       void on_textEdit_textChanged();

                                   private:
    Ui::MainWindow *ui;
    QString selectedPath;
    bool unsaved;

};
