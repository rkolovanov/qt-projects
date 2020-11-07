#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent): QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
    ui->pushButtonOkay->setEnabled(false);

    QRegExp regexp("[a-z]{1,5}[0-9]{1,5}");
    ui->lineEditInput->setValidator(new QRegExpValidator(regexp, this));

    connect(ui->lineEditInput, SIGNAL(textChanged()), this, SLOT(setPushButtonOkayEnabled()));
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::setPushButtonOkayEnabled() {
    ui->pushButtonOkay->setEnabled(ui->lineEditInput->hasAcceptableInput());
}

void Dialog::on_pushButton_clicked() {
    static bool open = false;

    ui->groupBox_2->setVisible(open);

    open = !open;
}
