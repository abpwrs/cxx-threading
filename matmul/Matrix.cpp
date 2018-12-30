//
// Created by Alex Powers on 2018-12-29.
//

#include "Matrix.h"

Matrix::Matrix(int *a[], int m, int n) : m(m), n(n) {

}

int Matrix::getNumThreads() const {
    return numThreads;
}

void Matrix::setNumThreads(int num_threads) {
    Matrix::numThreads = num_threads;
}

const Matrix::matrix_type &Matrix::getData() const {
    return data;
}

void Matrix::setData(const Matrix::matrix_type &data) {
    Matrix::data = data;
}

int Matrix::getM() const {
    return m;
}

int Matrix::getN() const {
    return n;
}
