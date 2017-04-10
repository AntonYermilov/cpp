#include "matrix.h"
#include <algorithm>

MatrixException::MatrixException(const char* msg) :
        msg(msg) {
}

const char* MatrixException::get() const {
    return msg;
}

Matrix::Matrix(size_t _h, size_t _w) :
        _h(_h), _w(_w) {
    allocate(_h, _w);
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (_h != other._h || _w != other._w)
        throw MatrixException("ADD: dimensions do not match.");
    Matrix res(_h, _w);
    for (size_t i = 0; i < _h; i++)
        for (size_t j = 0; j < _w; j++)
            res._data[i][j] = _data[i][j] + other._data[i][j];
    return res;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (_w != other._h)
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    Matrix res(_h, other._w);
    for (size_t i = 0; i < _h; i++)
        for (size_t j = 0; j < other._w; j++)
            for (size_t k = 0; k < _w; k++)
                res._data[i][j] += _data[i][k] * other._data[k][j];
    return res;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    return *this = *this + other;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    return *this = *this * other;
}

size_t Matrix::get(size_t i, size_t j) const {
    if (i >= _h || j >= _w)
        throw MatrixException("ACCESS: bad index.");
    return _data[i][j];
}

void Matrix::allocate(size_t h, size_t w) {
    if (h == 0 || w == 0)
        return;
    _data = std::vector<std::vector<int> >(h);
    for (size_t i = 0; i < h; i++)
        _data[i] = std::vector<int>(w, 0);
}

std::istream& operator>>(std::istream& in, Matrix& matrix) {
    size_t h, w;
    in >> h >> w;
    matrix = Matrix(h, w);
    for (size_t i = 0; i < h; i++)
        for (size_t j = 0; j < w; j++)
            in >> matrix._data[i][j];
    return in;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    for (size_t i = 0; i < matrix._h; i++) {
        for (size_t j = 0; j < matrix._w; j++)
            out << matrix._data[i][j] << ' ';
        out << std::endl;
    }
    return out;
}
