#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QDialog(parent) {
    labelInputText = new QLabel("&Введите текст:");
    lineEditInput = new QLineEdit();
    checkBoxLowercase = new QCheckBox("В нижнем регистре");
    checkBoxUppercase = new QCheckBox("В верхнем регистре");
    checkBoxReverse = new QCheckBox("В обратном порядке");
    pushButtonPrint = new QPushButton("Вывести");
    pushButtonClose = new QPushButton("Выход");
    isLowercaseMode = false;
    isReverseMode = false;

    QHBoxLayout* mainLayout = new QHBoxLayout;
    QVBoxLayout* leftLayout = new QVBoxLayout;
    QVBoxLayout* rightLayout = new QVBoxLayout;
    QHBoxLayout* inputLayout = new QHBoxLayout;

    inputLayout->addWidget(labelInputText);
    inputLayout->addWidget(lineEditInput);
    leftLayout->addLayout(inputLayout);
    leftLayout->addWidget(checkBoxUppercase);
    leftLayout->addWidget(checkBoxLowercase);
    leftLayout->addWidget(checkBoxReverse);
    rightLayout->addWidget(pushButtonPrint);
    rightLayout->addWidget(pushButtonClose);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    pushButtonPrint->setDefault(true);
    pushButtonPrint->setEnabled(false);
    labelInputText->setBuddy(lineEditInput);

    connect(lineEditInput, SIGNAL(textChanged(QString)), this, SLOT(lineEditInputChanged(QString)));
    connect(pushButtonClose, SIGNAL(clicked()), this, SLOT(close()));
    connect(pushButtonPrint, SIGNAL(clicked()), this, SLOT(pushButtonPrintClicked()));
    connect(checkBoxLowercase, SIGNAL(stateChanged(int)), this, SLOT(setLowercaseMode(int)));
    connect(checkBoxUppercase, SIGNAL(stateChanged(int)), this, SLOT(setUppercaseMode(int)));
    connect(checkBoxReverse, SIGNAL(stateChanged(int)), this, SLOT(setReverseMode(int)));

    setLayout(mainLayout);
    setWindowTitle("Text Printer v 0.1");
}

void MainWindow::pushButtonPrintClicked() {
    QMessageBox* messageBox = new QMessageBox();
    QString string = lineEditInput->text();

    if (isReverseMode) {
        QString temp;
        for (int i = string.size() - 1; i >= 0; i--){
            temp.push_back(string[i]);
        }
        string = temp;
    }

    if (isLowercaseMode) {
        string = string.toLower();
    } else if (isUppercaseMode) {
        string = string.toUpper();
    }

    messageBox->setText(string);
    messageBox->setIcon(QMessageBox::Information);
    messageBox->exec();
}

void MainWindow::lineEditInputChanged(QString string) {
    pushButtonPrint->setEnabled(!string.isEmpty());
}

void MainWindow::setReverseMode(int state){
    if (state == 0) {
        isReverseMode = false;
    } else {
        isReverseMode = true;
    }
}

void MainWindow::setLowercaseMode(int state){
    if (state == 0) {
        isLowercaseMode = false;
    } else {
        if (checkBoxUppercase->isChecked()) {
            isUppercaseMode = false;
            checkBoxUppercase->setChecked(false);
        }
        isLowercaseMode = true;
    }
}

void MainWindow::setUppercaseMode(int state){
    if (state == 0) {
        isUppercaseMode = false;
    } else {
        if (checkBoxLowercase->isChecked()) {
            isLowercaseMode = false;
            checkBoxLowercase->setChecked(false);
        }
        isUppercaseMode = true;
    }
}
