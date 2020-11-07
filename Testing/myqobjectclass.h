#pragma once
#include <QObject>

class MyQObjectClass: public QObject {

Q_OBJECT
Q_PROPERTY(bool value READ getValue WRITE setValue)

private:
    bool value_;

public:
    MyQObjectClass(QObject* parent = nullptr): QObject(parent), value_(false) {}

    bool getValue();
    void setValue(bool value);

};
