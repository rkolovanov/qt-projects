#include "myqobjectclass.h"

bool MyQObjectClass::getValue() {
    return value_;
}

void MyQObjectClass::setValue(bool value) {
     value_ = value;
}
