#pragma once
#include <vector>

namespace N {

    typedef unsigned long long int Size;

    template<typename Type>
    class Matrix {
    protected:
        std::vector<std::vector<Type>> data_;
        Size firstDimSize_ = 0;
        Size secondDimSize_ = 0;

    public:
        Matrix();
        Matrix(const Matrix& object);
        Matrix(Size firstDimSize, Size secondDimSize);

        Matrix& operator=(const Matrix& object);
        std::vector<Type>& operator[](Size index) {
            return data_[index];
        }
        const std::vector<Type>& operator[](Size index) const {
            return data_[index];
        }

        void setAllElements(Type value);
        Size getFirstDimSize() const;
        Size getSecondDimSize() const;
    };

    template<typename Type>
    Matrix<Type>::Matrix() {}

    template<typename Type>
    Matrix<Type>::Matrix(const Matrix<Type>& object) {
        data_ = object.data_;
    }

    template<typename Type>
    Matrix<Type>::Matrix(Size firstDimSize, Size secondDimSize) {
        firstDimSize_ = firstDimSize;
        secondDimSize_ = secondDimSize;
        data_ = std::vector<std::vector<Type>>(firstDimSize);

        for (Size i = 0; i < firstDimSize; i++) {
            data_[i].resize(secondDimSize);
        }
    }

    template<typename Type>
    Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type> &object) {
        data_ = object.data_;
    }

    template<typename Type>
    void Matrix<Type>::setAllElements(Type value) {
        for (Size i = 0; i < firstDimSize_; i++) {
            for(Size j = 0; j < secondDimSize_; j++) {
                data_[i][j] = value;
            }
        }
    }

    template<typename Type>
    Size Matrix<Type>::getFirstDimSize() const {
        return firstDimSize_;
    }

    template<typename Type>
    Size Matrix<Type>::getSecondDimSize() const {
        return secondDimSize_;
    }
}
