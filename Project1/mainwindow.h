#pragma once

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>


class MainWindow: public QDialog { Q_OBJECT
private:
    QLabel* labelInputText;
    QLineEdit* lineEditInput;
    QCheckBox* checkBoxLowercase;
    QCheckBox* checkBoxUppercase;
    QCheckBox* checkBoxReverse;
    QPushButton* pushButtonPrint;
    QPushButton* pushButtonClose;
    bool isReverseMode;
    bool isLowercaseMode;
    bool isUppercaseMode;

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void pushButtonPrintClicked();
    void lineEditInputChanged(QString);
    void setReverseMode(int);
    void setLowercaseMode(int);
    void setUppercaseMode(int);

};
