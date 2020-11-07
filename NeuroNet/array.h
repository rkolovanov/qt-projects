#pragma once

namespace N {

    typedef unsigned long long int Size;

    template <typename Type>
    class Array {
    protected:

        struct ArrayElement {
            Type value;
            ArrayElement* nextElement = nullptr;
            ArrayElement* prevElement = nullptr;

            ArrayElement() {}
            ArrayElement(Type val): value(val) {}
            ArrayElement(Type val, ArrayElement* prev): value(val), prevElement(prev) {}
        };

        ArrayElement* begin_ = nullptr;
        ArrayElement* end_ = nullptr;
        Size size_ = 0;

    public:

        class iterator {
        private:
            ArrayElement* element = nullptr;
            Size index_ = 0;

        public:
            iterator() {}
            iterator(ArrayElement* elem): element(elem) {}
            iterator(iterator& iter): element(iter.element) {}
            iterator(ArrayElement* elem, Size index): element(elem) { toIndex(index); }
            iterator(iterator& iter, Size index): element(iter.element) { toIndex(index); }

            iterator& operator=(iterator& iter) {
                element = iter.element;
                return *this;
            }

            iterator& operator=(ArrayElement* elem) {
                element = elem;
                return *this;
            }

            iterator& operator++() {
                if (element != nullptr) {
                    element = element->nextElement;
                }
                return *this;
            }

            iterator& operator++(int) {
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

            iterator& operator--(int) {
                iterator copy(*this);
                if (element != nullptr) {
                    element = element->prevElement;
                }
                return copy;
            }

            Type& operator*() { return element->value; }

            void toIndex(Size index) {
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

        Array() {}
        Array(Size size);
        Array(Array& object);
        ~Array();

        Array& operator=(Array& object);
        Type& operator[](Size index);
        Type operator[](Size index) const;

        void push(Type value);
        Type pop();
        void resize(Size newSize);
        void remove(Size index);
        void removeAll();
        Size size() const;
    };

}

namespace N {

    template<typename Type>
    Array<Type>::Array(Size size): begin_(new ArrayElement[size]), size_(size) {
        for (Size i = 1; i < size; i++) {
            begin_[i].prevElement = begin_ + (i - 1);
            begin_[i - 1].nextElement = begin_ + i;
        }
        end_ = begin_ + (size - 1);
    }

    template<typename Type>
    Array<Type>::Array(Array& object): begin_(new ArrayElement[object.size_]), size_(object.size_) {
        begin_[0].value = object[0];
        for (Size i = 1; i < object.size_; i++) {
            begin_[i].value = object[i];
            begin_[i].prevElement = begin_ + (i - 1);
            begin_[i - 1].nextElement = begin_ + i;
        }
        end_ = begin_ + (size_ - 1);
    }

    template<typename Type>
    Array<Type>::~Array() {
        removeAll();
    }

    template<typename Type>
    Array<Type>& Array<Type>::operator=(Array<Type>& object) {
        if (this != &object) {
            removeAll();

            size_ = object.size_;
            begin_ = new ArrayElement[size_];

            begin_[0].value = object[0];
            for (Size i = 1; i < object.size_; i++) {
                begin_[i].value = object[i];
                begin_[i].prevElement = begin_ + (i - 1);
                begin_[i - 1].nextElement = begin_ + i;
            }
            end_ = begin_ + (size_ - 1);
        }
        return *this;
    }

    template<typename Type>
    Type& Array<Type>::operator[](Size index) {
        iterator iter(begin_);
        for (Size i = 0; i < index; i++) {
            iter++;
        }
        return *iter;
    }

    template<typename Type>
    Type Array<Type>::operator[](Size index) const {
        iterator iter(begin_);
        for (Size i = 0; i < index; i++) {
            iter++;
        }
        return *iter;
    }

    template<typename Type>
    void Array<Type>::push(Type value) {
        if (begin_ == nullptr) {
            begin_ = new ArrayElement(value, end_);
            end_ = begin_;
        } else {
            end_->nextElement = new ArrayElement(value, end_);
            end_ = end_->nextElement;
        }

        size_++;
    }

    template<typename Type>
    Type Array<Type>::pop() {
        Type value = end_->value;

        end_ = end_->prevElement;
        delete end_->nextElement;
        end_->nextElement = nullptr;
        size_--;

        return value;
    }

    template<typename Type>
    void Array<Type>::resize(Size newSize) {
        if (newSize > size_) {
            while (newSize != size_) {
                end_->nextElement = new ArrayElement(end_);
                end_ = end_->nextElement;
                size_++;
            }

        } else if (newSize < size_) {
            while (newSize != size_) {
                end_ = end_->prevElement;
                delete end_->nextElement;
                size_--;
            }
            end_->nextElement = nullptr;
        }
    }

    template<typename Type>
    void Array<Type>::remove(Size index) {
        iterator iter = iterator(*this, index);
        ArrayElement* element = iter.element;

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
    void Array<Type>::removeAll() {
        ArrayElement* elem = begin_;
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
    Size Array<Type>::size() const {
        return size_;
    }

}
