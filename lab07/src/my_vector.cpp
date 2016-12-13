#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include "my_vector.h"

MyVector::MyVector() {
	_sz = 0;
	_cp = 2;
	_data = new int[_cp];
}
MyVector::MyVector(std::size_t init_capacity) {
	assert(init_capacity > 0);
	_sz = 0;
	_cp = init_capacity;
	_data = new int[_cp];
}
MyVector::~MyVector() {
	delete []_data;
}

std::size_t MyVector::size() {
	return _sz;
}
std::size_t MyVector::capacity() {
	return _cp;
}

void MyVector::set(std::size_t index, int value) {
	assert(0 <= index && index < _sz);
	_data[index] = value;
}
int MyVector::get(std::size_t index) {
	assert(0 <= index && index < _sz);
	return _data[index];
}

void MyVector::reserve(std::size_t new_capacity) {
	if (new_capacity <= _cp)
		return;
	int* new_data = new int[new_capacity];
	memcpy(new_data, _data, sizeof(_data[0]) * _sz);
	delete []_data;
	_cp = new_capacity;
	_data = new_data;
}
void MyVector::resize(std::size_t new_size) {
	if (new_size > _cp) {
		std::size_t new_capacity = _cp;
		while (new_capacity < new_size)
			new_capacity <<= 1;
		reserve(new_capacity);
	}
	memset(_data + _sz, 0, sizeof(_data[0]) * (new_size - _sz));
	_sz = new_size;
}

void MyVector::push_back(int value) {
	if (_sz == _cp)
		reserve(_cp * 2);
	_data[_sz++] = value;
}
void MyVector::insert(std::size_t index, int value) {
	assert(0 <= index && index <= _sz);
	push_back(0);
	for (std::size_t i = _sz - 1; i > index; i--)
		_data[i] = _data[i - 1];
	_data[index] = value;
}
void MyVector::erase(std::size_t index) {
	assert(0 <= index && index < _sz);
	for (std::size_t i = index; i < _sz - 1; i++)
		_data[i] = _data[i + 1];
	_sz--;
}
