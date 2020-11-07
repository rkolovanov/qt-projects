#pragma once

typedef unsigned long long int ulli;

template <typename Type>
class NArray {
protected:
    struct NArrayElement {
        Type value;
        NArrayElement* nextElement = nullptr;
        NArrayElement* prevElement = nullptr;

        NArrayElement() {}
        NArrayElement(Type val): value(val) {}
        NArrayElement(Type val, NArrayElement* prev): value(val), prevElement(prev) {}
        NArrayElement(NArrayElement* prev): prevElement(prev) {}
    };

    class iterator {
    private:
        NArrayElement* element = nullptr;
        ulli index_ = 0;

    public:
        iterator() {}
        iterator(NArrayElement* elem): element(elem) {}
        iterator(iterator& iter): element(iter.element) {}
        iterator(NArrayElement* elem, ulli index): element(elem) { toIndex(index); }
        iterator(iterator& iter, ulli index): element(iter.element) { toIndex(index); }

        iterator& operator=(iterator& iter) {
            element = iter.element;
            return *this;
        }
        iterator& operator=(NArrayElement* elem) {
            element = elem;
            return *this;
        }
        iterator& operator++() {
            if (element != nullptr) {
                element = element->nextElement;
            }
            return *this;
        }
        iterator operator++(int) {
            iterator copy(*this);
            if (element != nullptr) {
                element = element->nextElement;
            }
            return copy;
        }
        iterator& operator--() {
            if (element != nullptr) {
                element = element->prevElement;
            }
            return *this;
        }
        iterator operator--(int) {
            iterator copy(*this);
            if (element != nullptr) {
                element = element->prevElement;
            }
            return copy;
        }
        Type& operator*() { return element->value; }
        void toIndex(ulli index) {
            if (index > index_) {
                while (element->nextElement != nullptr && index_ != index) {
                    element = element->nextElement;
                    index_++;
                }
            } else if (index < index_) {
                while (element->prevElement != nullptr && index_ != index) {
                    element = element->prevElement;
                    index_++;
                }
            }
        }
    };

    NArrayElement* begin_ = nullptr;
    NArrayElement* end_ = nullptr;
    ulli size_ = 0;

public:
    NArray() {}
    NArray(ulli size);
    NArray(NArray& object);
    ~NArray();

    NArray& operator=(NArray& object);
    Type& operator[](ulli index);
    Type operator[](ulli index) const;

    void push(Type value);
    Type pop();
    void remove(ulli index);
    void removeAll();
    ulli size() const;
};

template<typename Type>
NArray<Type>::NArray(ulli size): begin_(new NArrayElement[size]), size_(size) {
    for (ulli i = 1; i < size; i++) {
        begin_[i].prevElement = begin_ + (i - 1);
        begin_[i - 1].nextElement = begin_ + i;
    }
    end_ = begin_ + (size - 1);
}

template<typename Type>
NArray<Type>::NArray(NArray& object): begin_(new NArrayElement[object.size_]), size_(object.size_) {
    begin_[0].value = object[0];
    for (ulli i = 1; i < object.size_; i++) {
        begin_[i].value = object[i];
        begin_[i].prevElement = begin_ + (i - 1);
        begin_[i - 1].nextElement = begin_ + i;
    }
    end_ = begin_ + (size_ - 1);
}

template<typename Type>
NArray<Type>::~NArray() {
    removeAll();
}

template<typename Type>
NArray<Type>& NArray<Type>::operator=(NArray<Type>& object) {
    if (this != &object) {
        removeAll();

        size_ = object.size_;
        begin_ = new NArrayElement[size_];

        begin_[0].value = object[0];
        for (ulli i = 1; i < object.size_; i++) {
            begin_[i].value = object[i];
            begin_[i].prevElement = begin_ + (i - 1);
            begin_[i - 1].nextElement = begin_ + i;
        }
        end_ = begin_ + (size_ - 1);
    }
    return *this;
}

template<typename Type>
Type& NArray<Type>::operator[](ulli index) {
    iterator iter(begin_);
    for (ulli i = 0; i < index; i++) {
        iter++;
    }
    return *iter;
}

template<typename Type>
Type NArray<Type>::operator[](ulli index) const {
    iterator iter(begin_);
    for (ulli i = 0; i < index; i++) {
        iter++;
    }
    return *iter;
}

template<typename Type>
void NArray<Type>::push(Type value) {
    end_->nextElement = new NArrayElement(value, end_);
    end_ = end_->nextElement;
    size_++;
}

template<typename Type>
Type NArray<Type>::pop() {
    Type value = end_->value;

    end_ = end_->prevElement;
    delete end_->nextElement;
    end_->nextElement = nullptr;
    size_--;

    return value;
}

template<typename Type>
void NArray<Type>::remove(ulli index) {
    iterator iter = iterator(*this, index);
    NArrayElement* element = iter.element;

    if (element != nullptr) {
    if (element->prevElement != nullptr && element->nextElement != nullptr) {
        element->prevElement->nextElement = element->nextElement;
        element = element->prevElement;
        delete element->nextElement->prevElement;
        element->nextElement->prevElement = element;
        size_--;
    } else if (element->prevElement == nullptr) {
        element = element->nextElement;
        delete element->prevElement;
        element->prevElement = nullptr;
        size_--;
        begin_ = element;
    } else if (element->nextElement == nullptr) {
        element = element->prevElement;
        delete element->nextElement;
        element->nextElement = nullptr;
        size_--;
        end_ = element;
    } else {
        delete element;
        element = nullptr;
        size_--;
    }
    }
}

template<typename Type>
void NArray<Type>::removeAll() {
    NArrayElement* elem = begin_;
    while (elem->nextElement != nullptr) {
        elem = elem->nextElement;
        delete elem->prevElement;
    }
    delete elem;

    begin_ = nullptr;
    end_ = nullptr;
    size_ = 0;
}

template<typename Type>
ulli NArray<Type>::size() const {
    return size_;
}
