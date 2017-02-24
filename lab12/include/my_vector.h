#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>
#include <cstddef>
#include <cstring>
#include <utility>
#include <cassert>

template <class T>
class my_vector {
public:
    my_vector<T>(const size_t& n = 0, const T& default_value = T()) {
        _capacity = 1;
        while (_capacity < n)
            _capacity *= 2;
        _size = n;
        _array = (T*) new char[_capacity * sizeof(T)];
        for (size_t i = 0; i < _size; i++)
            new (_array + i) T(default_value);
    }
    my_vector<T>(const my_vector<T>& other) {
        _capacity = other._capacity;
        _size = other._size;
        _array = (T*) new char[_capacity * sizeof(T)];
        for (size_t i = 0; i < _size; i++)
            new (_array + i) T(other[i]);
    }
    my_vector<T>& operator=(my_vector<T> other) {
        std::swap(_capacity, other._capacity);
        std::swap(_size, other._size);
        std::swap(_array, other._array);
        return *this;
    }
    ~my_vector<T>() {
        for (size_t i = 0; i < _size; i++)
            _array[i].~T();
        delete [](char*)_array;
    }

    size_t size() const {
        return _size;
    }
    size_t capacity() const {
        return _capacity;
    }
    bool empty() const {
        return _size == 0;
    }


    void reserve(size_t n) {
        if (n <= _capacity)
            return;
        
        while (_capacity < n)
            _capacity *= 2;
        T* new_array = (T*) new char[_capacity * sizeof(T)];
        for (size_t i = 0; i < _size; i++)
            new (new_array + i) T(_array[i]);
        std::swap(_array, new_array);
        
        for (size_t i = 0; i < _size; i++)
            new_array[i].~T();
        delete [](char*)new_array;
    }
    void resize(size_t n) {
        if (n > _capacity)
            reserve(n);
        while (_size < n)
            new (_array + _size++) T();
        while (_size > n)
            _array[--_size].~T();
    }

    T& operator[](size_t index) {
        return *(_array + index);
    }
    T& operator[](size_t index) const {
        return *(_array + index);
    }

    void push_back(const T& t) {
        if (_size == _capacity)
            reserve(2 * _capacity);
        new (_array + _size) T(t);
        _size++;
    }
    void pop_back() {
        _array[--_size].~T();
    }
    void clear() {
        while (_size)
            _array[--_size].~T();
    }

    bool operator==(const my_vector<T>& other) const {
        if (_capacity != other._capacity || _size != other._size)
            return false;
        for (size_t i = 0; i < _size; i++)
            if (_array[i] != other[i])
                return false;
        return true;
    }
    bool operator!=(const my_vector<T>& other) const {
        return !(*this == other);
    }
    
    friend std::ostream& operator<<(std::ostream& out, const my_vector<T>& vector) {
        for (size_t i = 0; i < vector.size(); i++)
            out << vector[i] << ' ';
        return out;
    }

private:
    size_t _capacity;
    size_t _size;
    T* _array;
};

#endif
