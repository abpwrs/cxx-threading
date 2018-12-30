//
// Created by Alex Powers on 2018-12-29.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cmath>
#include "Matrix.h"

typedef std::vector<std::vector<int>> matrix_type;

void print_matrix(matrix_type matrix) {
    for (std::vector<int> row: matrix) {
        for (int elem: row) {
            std::cout << elem << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
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

matrix_type matmul(const matrix_type &a, const matrix_type &b, const int &n_threads) {
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

    std::vector<std::thread> threads;
    threads.reserve(n_threads);
    for (int j = 0; j < n_threads; ++j) {
        threads.emplace_back(sub_mult, a, b, std::ref(out_matrix), offsets[j]); // start each thread
    }
    for (int j = 0; j < n_threads; ++j) {
        threads[j].join(); // wait for each thread to finish
    }
    return out_matrix;
}


int main() {
    const int n_threads = 4;
    const int m1 = 5;
    const int n1 = 5;
    const int m2 = 5;
    const int n2 = 5;

    matrix_type identity = {
            {2, 0, 0, 0, 0},
            {0, 2, 0, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 0, 2, 0},
            {0, 0, 0, 0, 2}};

    matrix_type matrix_1 = {
            {1, 2, 3, 4, 5},
            {5, 1, 2, 3, 4},
            {4, 5, 1, 2, 3},
            {3, 4, 5, 1, 2},
            {2, 3, 4, 5, 1}};

    print_matrix(identity);
    print_matrix(matrix_1);
    matrix_type out_matrix = matmul(identity, matrix_1, n_threads);
    print_matrix(out_matrix);
}


