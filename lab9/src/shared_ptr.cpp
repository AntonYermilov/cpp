#include <algorithm>

#include "shared_ptr.h"

shared_ptr::shared_ptr(Matrix* obj) {
  this->_storage = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other) {
  this->_storage = other._storage;
  this->_storage->incr();
}

shared_ptr& shared_ptr::operator=(const shared_ptr& other) {
  if (this == &other)
    return *this;

  shared_ptr tmp(other);
  std::swap(this->_storage, tmp._storage);
  return *this;
}

shared_ptr::~shared_ptr() {
  this->_storage->decr();
  if (this->_storage->getCounter() == 0) {
    delete this->_storage;
  }
}

Matrix* shared_ptr::ptr() const {
  return this->_storage->getObject();
}

bool shared_ptr::isNull() const {
  return !this->_storage->getObject();
}

void shared_ptr::reset(Matrix* obj) {
  if (this->ptr() == obj)
    return;
  shared_ptr tmp(obj);
  std::swap(this->_storage, tmp._storage);
}

Matrix* shared_ptr::operator->() const {
  return this->ptr();
}

Matrix& shared_ptr::operator*() const {
  return *this->ptr();
}

shared_ptr::Storage::Storage(Matrix* mtx) {
  this->_data = mtx;
  _ref_count = 1;
}

shared_ptr::Storage::~Storage() {
  delete this->_data;
}

void shared_ptr::Storage::incr() {
  this->_ref_count++;
}

void shared_ptr::Storage::decr() {
  this->_ref_count--;
}

int shared_ptr::Storage::getCounter() const {
  return _ref_count;
}

Matrix* shared_ptr::Storage::getObject() const {
  return _data;
}
