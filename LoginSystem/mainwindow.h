#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>


class UsersStorage {
public:
    struct User {
        QString username;
        QString password;
        QString name;

        User();
        User(QString, QString, QString);
    };

    struct Answer {
        bool success;
        QString data;
        User user;

        Answer();
        Answer(bool, QString, User);
    };

private:
    QVector<User> storage;

public:
    UsersStorage();
    Answer checkUserData(User);
    Answer addUser(User);

};

class RegisterDialog: public QDialog { Q_OBJECT
private:
    QLabel* labelUsernameText;
    QLabel* labelPasswordText;
    QLabel* labelNameText;
    QLineEdit* lineEditUsername;
    QLineEdit* lineEditPassword;
    QLineEdit* lineEditName;
    QPushButton* pushButtonRegister;
    QPushButton* pushButtonClose;
    UsersStorage* storage;

public:
    RegisterDialog(UsersStorage*, QWidget* parent = nullptr);

private slots:
    void pushButtonRegisterClicked();

};

class MainWindow: public QDialog { Q_OBJECT
private:
    QLabel* labelUsernameText;
    QLabel* labelPasswordText;
    QLineEdit* lineEditUsername;
    QLineEdit* lineEditPassword;
    QPushButton* pushButtonLogin;
    QPushButton* pushButtonRegister;
    QPushButton* pushButtonClose;
    UsersStorage* storage;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void pushButtonLoginClicked();
    void pushButtonRegisterClicked();
};
