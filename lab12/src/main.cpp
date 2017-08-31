#include <iostream>
#include <cstddef>
#include <cstring>
#include <utility>
#include <iomanip>

#include "my_vector.h"
#include "test_my_vector_methods.h"

class Product {
public:
    Product(const char* name = "None", int quantity = 0, double price = 0) {
        _name = new char[strlen(name) + 1];
        strcpy(_name, name);
        _quantity = quantity;
        _price = price;
    }
    Product(const Product& other) {
        _name = new char[strlen(other._name) + 1];
        strcpy(_name, other._name);
        _quantity = other._quantity;
        _price = other._price;
    }
    Product& operator=(Product other) {
        std::swap(_name, other._name);
        std::swap(_quantity, other._quantity);
        std::swap(_price, other._price);
        return *this;
    }
    ~Product() {
        delete []_name;
    }

    bool operator==(const Product& other) const {
        return strcmp(_name, other._name) == 0 && _quantity == other._quantity && _price == other._price;
    }
    bool operator!=(const Product& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& out, const Product& product) {
        out << product._name << ' ' << product._quantity << ' ' << std::setprecision(5) << std::fixed << product._price;
        return out;
    }
    
private:
    char* _name;
    int _quantity;
    double _price;
};

template<class T>
void test_my_vector(const T& arg1, const T& arg2) {
    test_my_vector_methods<T>::run(arg1, arg2);
    
    my_vector<T> v;
    v.push_back(arg1);
    v.push_back(arg2);
    v.resize(5);
    v[3] = arg1;
    std::cout << v << std::endl;
}

int main() {
    
    test_my_vector<int>(13, 566);
    test_my_vector<Product>(Product("Cookies", 100, 65.0), Product("Car", 15, 683000.11235));

    return 0;
}
