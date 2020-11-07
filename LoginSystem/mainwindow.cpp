#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QDialog(parent) {
    labelUsernameText = new QLabel("Имя пользователя:");
    labelPasswordText = new QLabel("Пароль:");
    lineEditUsername = new QLineEdit();
    lineEditPassword = new QLineEdit();
    pushButtonLogin = new QPushButton("Авторизация");
    pushButtonRegister = new QPushButton("Регистрация");
    pushButtonClose = new QPushButton("Закрыть");
    storage = new UsersStorage;

    QHBoxLayout* mainLayout = new QHBoxLayout();
    QVBoxLayout* leftLayout = new QVBoxLayout();
    QVBoxLayout* rightLayout = new QVBoxLayout();
    QHBoxLayout* usernameInputLayout = new QHBoxLayout();
    QHBoxLayout* passwordInputLayout = new QHBoxLayout();

    usernameInputLayout->addWidget(labelUsernameText);
    usernameInputLayout->addWidget(lineEditUsername);
    passwordInputLayout->addWidget(labelPasswordText);
    passwordInputLayout->addWidget(lineEditPassword);
    leftLayout->addLayout(usernameInputLayout);
    leftLayout->addLayout(passwordInputLayout);
    rightLayout->addWidget(pushButtonLogin);
    rightLayout->addWidget(pushButtonRegister);
    rightLayout->addWidget(pushButtonClose);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    connect(pushButtonLogin, SIGNAL(clicked()), this, SLOT(pushButtonLoginClicked()));
    connect(pushButtonRegister, SIGNAL(clicked()), this, SLOT(pushButtonRegisterClicked()));
    connect(pushButtonClose, SIGNAL(clicked()), this, SLOT(close()));

    setWindowTitle("Authorization System v 0.2");
}

MainWindow::~MainWindow() {
    delete storage;
}

void MainWindow::pushButtonLoginClicked() {
    QMessageBox* messageBox = new QMessageBox();
    QString username = lineEditUsername->text();
    QString password = lineEditPassword->text();
    QString info;

    UsersStorage::Answer answer = storage->checkUserData(UsersStorage::User(username, password, ""));

    if (answer.success) {
        messageBox->setIcon(QMessageBox::Information);
        info = "Приветствую, " + answer.user.name + "!";
    } else {
        messageBox->setIcon(QMessageBox::Warning);
        info = answer.data;
    }

    messageBox->setText(info);
    messageBox->exec();
}

void MainWindow::pushButtonRegisterClicked() {
    RegisterDialog* regDialog = new RegisterDialog(storage);

    regDialog->show();
    regDialog->exec();
}

UsersStorage::UsersStorage() {

}

UsersStorage::Answer UsersStorage::addUser(UsersStorage::User user) {
    bool isUnique = true;

    for (int i = 0; i < storage.size(); i++) {
        if (storage[i].username == user.username) {
            isUnique = false;
            break;
        }
    }

    if (!isUnique) {
        return UsersStorage::Answer(false, "Пользователь с таким именем уже существует!", user);
    }

    storage.push_back(user);
    return UsersStorage::Answer(true, "Вы успешно зарегистрированы!", user);
}

UsersStorage::Answer UsersStorage::checkUserData(UsersStorage::User user) {
    bool isUsernameExist = false;
    bool isPasswordCorrect = false;

    for (int i = 0; i < storage.size(); i++) {
        if (storage[i].username == user.username) {
            isUsernameExist = true;
            if (storage[i].password == user.password) {
                isPasswordCorrect = true;
                user.name = storage[i].name;
            }
            break;
        }
    }

    if (!isUsernameExist) {
        return UsersStorage::Answer(false, "Пользователя с таким именем не существует!", user);
    }

    if (!isPasswordCorrect) {
        return UsersStorage::Answer(false, "Неверный пароль!", user);
    }

    return UsersStorage::Answer(true, "", user);
}

UsersStorage::Answer::Answer(bool s, QString d, UsersStorage::User u) {
    success = s;
    data = d;
    user = u;
}

UsersStorage::User::User() {
    username = "";
    password = "";
    name = "";
}

UsersStorage::User::User(QString u, QString p, QString n) {
    username = u;
    password = p;
    name = n;
}

RegisterDialog::RegisterDialog(UsersStorage* s, QWidget* parent): QDialog(parent) {
    labelUsernameText = new QLabel("Имя пользователя: ");
    labelPasswordText = new QLabel("Пароль: ");
    labelNameText = new QLabel("Ваше имя: ");
    lineEditUsername = new QLineEdit();
    lineEditPassword = new QLineEdit();
    lineEditName = new QLineEdit();
    pushButtonRegister = new QPushButton("Зарегистрироваться");
    pushButtonClose = new QPushButton("Закрыть");
    storage = s;

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QVBoxLayout* upperLayout = new QVBoxLayout();
    QHBoxLayout* lowerLayout = new QHBoxLayout();
    QHBoxLayout* inputUsernameLayout = new QHBoxLayout();
    QHBoxLayout* inputPasswordLayout = new QHBoxLayout();
    QHBoxLayout* inputNameLayout = new QHBoxLayout();

    inputNameLayout->addWidget(labelNameText);
    inputNameLayout->addWidget(lineEditName);
    inputPasswordLayout->addWidget(labelPasswordText);
    inputPasswordLayout->addWidget(lineEditPassword);
    inputUsernameLayout->addWidget(labelUsernameText);
    inputUsernameLayout->addWidget(lineEditUsername);
    upperLayout->addLayout(inputUsernameLayout);
    upperLayout->addLayout(inputPasswordLayout);
    upperLayout->addLayout(inputNameLayout);
    lowerLayout->addWidget(pushButtonRegister);
    lowerLayout->addWidget(pushButtonClose);
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    connect(pushButtonRegister, SIGNAL(clicked()), this, SLOT(pushButtonRegisterClicked()));
    connect(pushButtonClose, SIGNAL(clicked()), this, SLOT(close()));

    setLayout(mainLayout);
    setWindowTitle("Регистрация");
}

void RegisterDialog::pushButtonRegisterClicked() {
    QMessageBox* messageBox = new QMessageBox();
    UsersStorage::User user(lineEditUsername->text(), lineEditPassword->text(), lineEditName->text());

    UsersStorage::Answer answer = storage->addUser(user);

    if (answer.success) {
        messageBox->setIcon(QMessageBox::Information);
    } else {
        messageBox->setIcon(QMessageBox::Warning);
    }

    messageBox->setText(answer.data);
    messageBox->exec();
}
