#pragma once

#include <QDialog>
#include <QRegExpValidator>

namespace Ui {
    class Dialog;
}

class Dialog: public QDialog { Q_OBJECT
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

private slots:
    void setPushButtonOkayEnabled();

                               void on_pushButton_clicked();
                             };
