#include <cassert>
#include<iostream>
#include "matrix.h"

using namespace std;

bool createMatrixTest() {
    int arr[3][3] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    Matrix<int> mat(arr, 3);
    for (size_t i = 0; i != 3; ++i)
        for (size_t j = 0; j != 3; ++j)
            assert(mat[i][j] == arr[i][j]);
    return true;
}

bool setMatrixTest() {
    int arr[3][3] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    Matrix<int> mat(arr, 3);
    mat.Set(1, 1, 100);
    assert(mat[1][1] == 100);
    return true;
}

bool createMatrixBasedOnMatrixTest() {
    int arr[3][3] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    Matrix<int> mat(arr, 3);
    Matrix<int> mat2(mat);
    for (size_t i = 0; i != 3; ++i)
        for (size_t j = 0; j != 3; ++j)
            assert(mat2[i][j] == arr[i][j]);
    return true;
}

bool addMatrixTest() {
    int arr[3][3] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    Matrix<int> mat(arr, 3);
    Matrix<int> mat2(mat);
    mat2.Add(mat);
    for (size_t i = 0; i != 3; ++i)
        for (size_t j = 0; j != 3; ++j)
            assert(mat2[i][j] == (arr[i][j] * 2));
    return true;
}

bool multMatrixTest() {
    int arr[3][3] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    Matrix<int> mat(arr, 3);
    mat.Multiply(3);
    for (size_t i = 0; i != 3; ++i)
        for (size_t j = 0; j != 3; ++j)
            assert(mat[i][j] == (arr[i][j] * 3));
    return true;
}

bool matMultMatrixTest() {
    int arr[3][3] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    int arr2[3][3] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
    Matrix<int> mat(arr, 3);
    Matrix<int> mat2(arr2, 3);
    mat.Multiply(mat2);
    for (size_t i = 0; i != 3; ++i)
        for (size_t j = 0; j != 3; ++j)
            assert(mat[i][j] == arr[i][j]);
    return true;
}

bool multLineMatrixTest() {
    int arr[3][3] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    Matrix<int> mat(arr, 3);
    mat.LineMultiply(1, 3);
    for (size_t j = 0; j != 3; ++j)
        assert(mat[1][j] == (arr[1][j] * 3));
    return true;
}

bool transpMatrixTest() {
    int arr[3][3] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    Matrix<int> mat(arr, 3);
    mat.Transponition();
    for (size_t i = 0; i != 3; ++i)
        for (size_t j = 0; j != 3; ++j)
            assert(mat[j][i] == arr[i][j]);
    return true;
}

bool swapMatrixTest() {
    int arr[3][3] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    Matrix<int> mat(arr, 3);
    mat.SwapLines(0, 2);
    for (size_t i = 0; i != 3; ++i)
        assert(mat[0][i] == arr[2][i]);
    for (size_t i = 0; i != 3; ++i)
        assert(mat[2][i] == arr[0][i]);
    return true;
}

bool (*testFunctions[])() = {
    createMatrixTest,
    setMatrixTest,
    createMatrixBasedOnMatrixTest,
    addMatrixTest,
    multMatrixTest,
    matMultMatrixTest,
    multLineMatrixTest,
    transpMatrixTest,
    swapMatrixTest
};

void runAllTests() {
    for (size_t i = 0; i < sizeof(testFunctions) / sizeof(testFunctions[0]); ++i) {
        if (testFunctions[i]()) {
            cout << " >>> " << i + 1 << ". Test passed!\n";
        } else {
            cout << " >>> " << i + 1 << ". Test failed!\n";
        }
    }
}
