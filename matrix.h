#pragma once
#include"ArraySequence.h"

template<class T>
class Matrix {
    private:
        ArraySequence<ArraySequence<T>> baseMatrix;
        size_t size;
    public:
        Matrix() {
            ArraySequence<ArraySequence<T>> tmpMatrix(0);
            baseMatrix = tmpMatrix;
        };
        
        Matrix(size_t size) {
            this->size = size;
            ArraySequence<ArraySequence<T>> tmpMatrix(size);
            for (size_t i = 0; i != size; ++i) {
                ArraySequence<T> tmpVec(size);
                tmpMatrix[i] = tmpVec;
            }
            baseMatrix = tmpMatrix;
        };
        template<size_t n, size_t m> 
        Matrix(T (&items)[n][m], size_t size) {
            this->size = size;
            ArraySequence<ArraySequence<T>> tmpMatrix(size);
            for (size_t i = 0; i != size; ++i) {
                ArraySequence<T> tmpVec(items[i], size);
                tmpMatrix[i] = tmpVec;
            }
            baseMatrix = tmpMatrix;
        };
        void Set(size_t i, size_t j, T elem) {
            this->baseMatrix.Getz(i).Set(j, elem);
        }
        Matrix(const Matrix<T>& matrix) {
            baseMatrix = matrix.baseMatrix;
            size = matrix.getSize();
        };
        size_t const getSize() const {
            return size;
        }
        Matrix Add(const Matrix& other) {
            for (size_t i = 0; i != size; ++i) {
                for (size_t j = 0; j != size; ++j) {
                    this->baseMatrix[i][j] += other.baseMatrix[i][j];
                }
            }
            return *this;
        }
        Matrix Multiply(const int& k) {
            for (size_t i = 0; i != size; ++i) {
                for (size_t j = 0; j != size; ++j) {
                    this->baseMatrix[i][j] *= k;
                }
            }
            return *this;
        }
        Matrix LineMultiply(const size_t& index, const int& k) {
            for (size_t j = 0; j != size; ++j) {
                this->baseMatrix[index][j] *= k;
            }
            return *this;
        }
        Matrix Transponition() {
            for (size_t i = 0; i != size; ++i) {
                for (size_t j = i; j != size; ++j) {
                    T tmp1 = baseMatrix[i][j];
                    T tmp2 = baseMatrix[j][i];
                    this->Set(i, j, tmp2);
                    this->Set(j, i, tmp1);
                }
            }
            return *this;
        }
        Matrix SwapLines(const int& index1, const int& index2) {
            for (size_t i = 0; i != size; ++i) {
                for (size_t j = 0; j != size; ++j) {
                    swap(this->baseMatrix[index1][j], this->baseMatrix[index2][j]);
                }
            }
            return *this;
        }
        Matrix Multiply(const Matrix<T>& matrix) {
            if (matrix.getSize() != this->size)
                throw length_error("Lengths are not equals!");
            for (size_t i = 0; i != size; ++i) {
                for (size_t j = 0; j != size; ++j) {
                    int tmp = 0;
                    for (size_t k = 0; k != size; ++k) {
                        tmp += (*this)[i][k] * matrix[k][j];
                    }
                    this->Set(i, j, tmp);
                }
            }
            return *this;
        }
        Matrix AddLineToLine(const int& index1, const int& index2, const int& k) {
            for (size_t i = 0; i != size; ++i) {
                for (size_t j = 0; j != size; ++j) {
                    this->baseMatrix[index1][j] += this->baseMatrix[index2][j] * k;
                }
            }
            return *this;
        }
        ArraySequence<T> operator[] (size_t index) const {
            return this->baseMatrix[index];
        }
        Matrix<T>& operator= (const Matrix& other) {
            this->baseMatrix = other.baseMatrix;
            this->size = other.getSize();
            return *this;
        }
        Matrix<T> operator+ (const Matrix& other) const {
            Matrix<T> tmp(this->getSize());
            tmp = *this;
            return tmp.Add(other);
        }
        Matrix<T> operator* (const int& k) const {
            Matrix<T> tmp(this->getSize());
            tmp = *this;
            return tmp.Multiply(k);
        }
        Matrix<T> operator- (const Matrix& other) const {
            Matrix<T> tmp(this->getSize());
            tmp = *this;
            return tmp.Add(other*(-1));
        }
};
