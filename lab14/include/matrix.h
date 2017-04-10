#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstddef>
#include <vector>

class MatrixException {
public:
    MatrixException(const char* msg = "None");
    const char* get() const;
private:
    const char* msg;
};

class Matrix {
public:
    Matrix(size_t h = 0, size_t w = 0);

    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    size_t get(size_t i, size_t j) const;

    friend std::istream& operator>>(std::istream& in, Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

private:
    void allocate(size_t h, size_t w);

    size_t _h, _w;
    std::vector<std::vector<int> > _data;
};


#endif
