//
// Created by Alex Powers on 2018-12-29.
//

#ifndef CXX_THREADING_MATRIX_H
#define CXX_THREADING_MATRIX_H

#include <vector>
#include <thread>
#include <cmath>
#include <iostream>
#include <sstream>

typedef std::vector <std::vector<int>> matrix_type;

class Matrix {
public:

    int getM() const;

    int getN() const;

    Matrix(matrix_type in, int m, int n);

    int getNumThreads() const;

    void setNumThreads(int num_threads);

    const matrix_type &getData() const;

    void setData(const matrix_type &data);

    std::string toString();

    void print();

    Matrix operator*(const Matrix &rhs);

private:
    int numThreads = 4;
    matrix_type data;
    int m;
    int n;

    matrix_type matmul(const matrix_type &a, const matrix_type &b, const int &n_threads);


};

void sub_mult(matrix_type a, matrix_type b, matrix_type &out, int *bounds);


#endif //CXX_THREADING_MATRIX_H
