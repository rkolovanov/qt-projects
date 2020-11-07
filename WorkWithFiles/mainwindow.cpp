#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    ui->statusBar->showMessage("Готов к работе!");
    unsaved = false;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    openFile(QFileDialog::getOpenFileName(this, tr("Открыть файл")));
}

void MainWindow::on_actionSave_triggered() {
    if (selectedPath == "") {
        on_actionSaveAs_triggered();
    } else {
        openFile(selectedPath);
    }
}

void MainWindow::openFile(QString path) {
    if (path == nullptr) {
        return;
    }

    QFile file(path);

    if (!file.exists()) {
        QMessageBox::information(this, "Открыть файл", "Ошибка! Файл не существует.");
        return;
    } else if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(this, "Открыть файл", "Ошибка! Нет доступа к файлу.");
        return;
    }

    selectedPath = path;
    QTextStream textStream(&file);
    QString buffer = textStream.readAll();
    ui->textEdit->setText(buffer);
    setWindowTitle(file.fileName() + " - " + path);
    ui->statusBar->showMessage("Файл: " + path);

    file.flush();
    file.close();
}

void MainWindow::saveFile(QString path) {
    QFile file(path);

    if (!file.exists() &&!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::information(this, "Сохранить файл", "Ошибка! Нет доступа к файлу.");
            return;
    }

    QTextStream textStream(&file);
    textStream << ui->textEdit->toPlainText();
    ui->statusBar->showMessage("Сохранено: " + path);

    if (unsaved) {
        setWindowTitle("");
    }

    file.close();
}


void MainWindow::on_actionSaveAs_triggered() {
    saveFile(QFileDialog::getSaveFileName(this, tr("Сохранить файл")));
}

void MainWindow::on_actionClose_triggered() {
    if (unsaved && QMessageBox::question(this, "Сохранение", "Сохранить текущий файл?") == QMessageBox::No) {
        return;
    }

    on_actionSave_triggered();
}

void MainWindow::on_textEdit_textChanged() {
    unsaved = true;
    setWindowTitle("*" + this->windowTitle());
}
