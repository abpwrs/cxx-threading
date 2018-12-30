//
// Created by Alex Powers on 2018-12-29.
//

#include "Matrix.h"

Matrix::Matrix(matrix_type in, int m, int n) : m(m), n(n) {
    data = in;

}

int Matrix::getNumThreads() const {
    return numThreads;
}

void Matrix::setNumThreads(int num_threads) {
    Matrix::numThreads = num_threads;
}

const matrix_type &Matrix::getData() const {
    return data;
}

void Matrix::setData(const matrix_type &data) {
    this->data = data;
}

int Matrix::getM() const {
    return m;
}

int Matrix::getN() const {
    return n;
}

std::string Matrix::toString() {
    std::stringstream ss;
    for (std::vector<int> row: data) {
        for (int elem: row) {
            ss << elem << ", ";
        }
        ss << std::endl;
    }
    ss << std::endl << std::endl;
    return ss.str();
}

void Matrix::print() {
    std::cout << m << "X" << n << " matrix\n";
    std::cout << toString();
}

void sub_mult(matrix_type a, matrix_type b, matrix_type &out, int *bounds) {
    for (int row = bounds[0]; row < bounds[1]; ++row) {
        int max_cols = (int) out[row].size();
        for (int col = 0; col < max_cols; ++col) {
            int val = 0;
            for (int c = 0; c < a[0].size(); ++c) {
                val += a[row][c] * b[c][col];
            }
            out[row][col] = val;
        }
    }
}

matrix_type Matrix::matmul(const matrix_type &a, const matrix_type &b, const int &n_threads) {
    matrix_type out_matrix;
    // setup matrix size
    int m_out = (int) a.size();
    int n_out = (int) b[0].size();
    for (int i = 0; i < m_out; ++i) {
        out_matrix.push_back(std::vector<int>(n_out));
    }
    // 0, 0+size/threads, ... ,end
    int offsets[n_threads][2];
    int step = (int) floor(m_out / n_threads); // floor is probably redundant due to integer truncation
    for (int i = 0; i < n_threads; ++i) {
        offsets[i][0] = i * step;
        offsets[i][1] = (i + 1) * step;
        if (i == n_threads - 1) { // if last thread
            offsets[i][1] = m_out; // the last thread will go to the end of the matrix
        }
    }

    std::vector <std::thread> threads;
    threads.reserve(n_threads);
    for (int j = 0; j < n_threads; ++j) {
        threads.emplace_back(sub_mult, a, b, std::ref(out_matrix), offsets[j]); // start each thread
    }
    for (int j = 0; j < n_threads; ++j) {
        threads[j].join(); // wait for each thread to finish
    }
    return out_matrix;
}

Matrix Matrix::operator*(const Matrix &rhs) {
    matrix_type out = matmul(data, rhs.data, numThreads);
    return Matrix(out, out.size(), out[0].size());
}
