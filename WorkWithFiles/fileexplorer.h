#pragma once

#include <QDialog>
#include <QPushButton>


namespace Ui {
    class FileExplorer;
}

class FileExplorer: public QDialog { Q_OBJECT
public:
    explicit FileExplorer(QWidget *parent = nullptr);
    ~FileExplorer();

private:
    Ui::FileExplorer *ui;

private slots:
    void sendFilePath();

signals:
    void onFilePathEntered(QString);

};
