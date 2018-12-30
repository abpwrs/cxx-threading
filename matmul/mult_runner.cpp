//
// Created by Alex Powers on 2018-12-29.
//

#include "Matrix.h"

int main() {
    const int n_threads = 4;
    const int m1 = 5;
    const int n1 = 5;
    const int m2 = 5;
    const int n2 = 5;

    matrix_type identity = {
            {2, 0, 0, 0, 1},
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

    // num threads defaults to 4 but can be set to different values
    Matrix I = Matrix(identity, m1, n1);
    Matrix M = Matrix(matrix_1, m2, n2);
    std::cout<<"I\n";
    I.print();
    std::cout<<"M\n";
    M.print();
    Matrix O1 = I * M;
    std::cout<<"IxM\n";
    O1.print();
    Matrix O2 = M * I;
    std::cout<<"MxI\n";
    O2.print();
}


