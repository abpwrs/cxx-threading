//
// Created by Alex Powers on 2018-12-29.
//

#ifndef CXX_THREADING_MATRIX_H
#define CXX_THREADING_MATRIX_H

#include <vector>

class Matrix {
public:
    typedef std::vector<std::vector<int>> matrix_type;

    int getM() const;

    int getN() const;

    Matrix(int *a[], int m, int n);

    int getNumThreads() const;

    void setNumThreads(int num_threads);

    const matrix_type &getData() const;

    void setData(const matrix_type &data);


private:
    int numThreads = 4;
    matrix_type data;
    int m;
    int n;

};


#endif //CXX_THREADING_MATRIX_H
