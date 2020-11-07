#include "fileexplorer.h"
#include "ui_fileexplorer.h"

FileExplorer::FileExplorer(QWidget *parent): QDialog(parent), ui(new Ui::FileExplorer) {
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(sendFilePath()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(close()));
}

FileExplorer::~FileExplorer() {
    delete ui;
}

void FileExplorer::sendFilePath() {
    emit(onFilePathEntered(ui->lineEditInput->text()));
    close();
}
