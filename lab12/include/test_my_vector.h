#ifndef TEST_MY_VECTOR_H
#define TEST_MY_VECTOR_H

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <typeinfo>

#include "my_vector.h"

template<class T>
class test_my_vector_methods {
public:
    static void run(const T& arg1, const T& arg2) {
        total = 0;
        failed = 0;

        srand(0);

        test_constructor_default();
        test_constructor_default_size();
        test_constructor_default_size_and_value(arg1);
        test_constructor_copy(arg1, arg2);
        test_constructor_assign(arg1, arg2);

        test_size();
        test_capacity();
        test_empty();

        test_reserve();
        test_resize();

        test_push_back(arg1);
        test_pop_back();
        test_clear();

        test_operator_square_brackets(arg1, arg2);
        test_operator_equal(arg1, arg2);

        print_statistics();
    }
private:
    test_my_vector_methods<T>();

    static void print_statistics() {
        std::cerr << std::endl;
        std::cerr << "=== total: " << total << std::endl;
        std::cerr << "=== failed: " << failed << std::endl;
        std::cerr << std::endl;
    }

    static void check(bool ok, const char* file, const char* function, int line) {
        if (!ok) {
            failed++;
            std::cerr << "TEST FAILED:" << std::endl;
            std::cerr << "FILE: " << file << std::endl;
            std::cerr << "FUNCTION: " << function << std::endl;
            std::cerr << "LINE: " << line << std::endl;
            std::cerr << std::endl;
        }
        total++;
    }

    static size_t gen_size() {
        size_t sz = rand() % MAX_SIZE + 1;
        return sz;
    }
    static size_t gen_capacity(const size_t& sz) {
        size_t cap = 1;
        while (cap < sz)
            cap *= 2;
        return cap;
    }
    static my_vector<T> gen_vector(const size_t& sz, const T& arg1, const T& arg2) {
        my_vector<T> v(sz);
        for (size_t i = 0; i < sz; i++)
            v[i] = rand() & 1 ? arg1 : arg2;
        return v;
    }

    static void test_constructor_default() {
        my_vector<T> v;
        check(v.size() == 0 && v.capacity() == 1, __FILE__, __FUNCTION__, __LINE__);
    }

    static void test_constructor_default_size() {
        bool ok = true;

        size_t sz = gen_size();
        my_vector<T> v(sz);
        
        ok &= v.size() == sz && v.capacity() == gen_capacity(sz);
        for (size_t i = 0; i < sz; i++)
            ok &= v[i] == T();

        check(ok, __FILE__, __FUNCTION__, __LINE__);
    }
    static void test_constructor_default_size_and_value(const T& arg) {
        bool ok = true;

        size_t sz = gen_size();
        my_vector<T> v(sz, arg);
        
        ok &= v.size() == sz && v.capacity() == gen_capacity(sz);
        for (size_t i = 0; i < sz && ok; i++)
            ok &= v[i] == arg;
            
        check(ok, __FILE__, __FUNCTION__, __LINE__);
    }
    static void test_constructor_copy(const T& arg1, const T& arg2) {
        size_t sz = gen_size();
        my_vector<T> v1(sz);
        for (size_t i = 0; i < sz; i++)
            v1[i] = rand() & 1 ? arg1 : arg2;
        my_vector<T> v2(v1);

        check(v1 == v2, __FILE__, __FUNCTION__, __LINE__);
    }
    static void test_constructor_assign(const T& arg1, const T& arg2) {
        size_t sz = gen_size();
        my_vector<T> v1(gen_vector(sz, arg1, arg2));
        my_vector<T> v2(1, arg1);
        v2 = v1;

        check(v1 == v2, __FILE__, __FUNCTION__, __LINE__);
    }

    static void test_size() {
        my_vector<T> v1;
        my_vector<T> v2(128);
        my_vector<T> v3(MAX_SIZE);
        my_vector<T> v4(v2);

        check(v1.size() == 0, __FILE__, __FUNCTION__, __LINE__);
        check(v2.size() == 128, __FILE__, __FUNCTION__, __LINE__);
        check(v3.size() == MAX_SIZE, __FILE__, __FUNCTION__, __LINE__);
        check(v4.size() == v2.size(), __FILE__, __FUNCTION__, __LINE__);

        v4 = v3;
        check(v4.size() == v3.size(), __FILE__, __FUNCTION__, __LINE__);
    }
    static void test_capacity() {
        my_vector<T> v1;
        my_vector<T> v2(128);
        my_vector<T> v3(MAX_SIZE);
        my_vector<T> v4(v2);
     
        check(v1.capacity() == 1, __FILE__, __FUNCTION__, __LINE__);
        check(v2.capacity() == 128, __FILE__, __FUNCTION__, __LINE__);
        check(v3.capacity() == gen_capacity(MAX_SIZE), __FILE__, __FUNCTION__, __LINE__);
        check(v4.capacity() == v2.capacity(), __FILE__, __FUNCTION__, __LINE__);
        
        v4 = v3;
        check(v4.capacity() == v3.capacity(), __FILE__, __FUNCTION__, __LINE__);
    }
    static void test_empty() {
        my_vector<T> v1;
        my_vector<T> v2(1);

        check(v1.empty() == (v1.size() == 0), __FILE__, __FUNCTION__, __LINE__);
        check(v2.empty() == (v2.size() == 0), __FILE__, __FUNCTION__, __LINE__);
    }

    static void test_reserve() {
        my_vector<T> v(10);
        
        v.reserve(31);
        check(v.size() == 10 && v.capacity() == 32, __FILE__, __FUNCTION__, __LINE__);
        
        v.reserve(64);
        check(v.size() == 10 && v.capacity() == 64, __FILE__, __FUNCTION__, __LINE__);
    
        v.reserve(129);
        check(v.size() == 10 && v.capacity() == 256, __FILE__, __FUNCTION__, __LINE__);
        
        v.reserve(1);
        check(v.size() == 10 && v.capacity() == 256, __FILE__, __FUNCTION__, __LINE__);
    }
    static void test_resize() {
        my_vector<T> v(10);

        v.resize(31);
        check(v.size() == 31 && v.capacity() == 32, __FILE__, __FUNCTION__, __LINE__);
        
        v.resize(64);
        check(v.size() == 64 && v.capacity() == 64, __FILE__, __FUNCTION__, __LINE__);
        
        v.resize(129);
        check(v.size() == 129 && v.capacity() == 256, __FILE__, __FUNCTION__, __LINE__);

        v.resize(1);
        check(v.size() == 1 && v.capacity() == 256, __FILE__, __FUNCTION__, __LINE__);
    }

    static void test_push_back(const T& arg) {
        my_vector<T> v1;
        my_vector<T> v2(127);
        my_vector<T> v3(128);

        v1.push_back(arg);
        v2.push_back(arg);
        v3.push_back(arg);

        check(v1.size() == 1 && v1.capacity() == 1 && v1[0] == arg, __FILE__, __FUNCTION__, __LINE__);
        check(v2.size() == 128 && v2.capacity() == 128 && v2[127] == arg, __FILE__, __FUNCTION__, __LINE__);
        check(v3.size() == 129 && v3.capacity() == 256 && v3[128] == arg, __FILE__, __FUNCTION__, __LINE__);
    }
    static void test_pop_back() {
        my_vector<T> v1(128);
        my_vector<T> v2(129);

        v1.pop_back();
        v2.pop_back();

        check(v1.size() == 127 && v1.capacity() == 128, __FILE__, __FUNCTION__, __LINE__);
        check(v2.size() == 128 && v2.capacity() == 256, __FILE__, __FUNCTION__, __LINE__);
    }
    static void test_clear() {
        my_vector<T> v1;
        my_vector<T> v2(128);

        v1.clear();
        v2.clear();

        check(v1.size() == 0 && v1.capacity() == 1, __FILE__, __FUNCTION__, __LINE__);
        check(v2.size() == 0 && v2.capacity() == 128, __FILE__, __FUNCTION__, __LINE__);
    }

    static void test_operator_square_brackets(const T& arg1, const T& arg2) {
        bool ok = true;

        size_t sz = gen_size();
        my_vector<T> v(gen_vector(sz, arg1, arg2));
        
        for (int i = 0; i < 10; i++) {
            size_t id = rand() % sz;
            ok &= ((char*) &v[id] == (char*) &v[0] + id * sizeof(T));
        }

        check(ok, __FILE__, __FUNCTION__, __LINE__);
    }
    static void test_operator_equal(const T& arg1, const T& arg2) {
        size_t sz = gen_size();
        
        my_vector<T> v1(sz), v2(sz);
        for (size_t i = 0; i < sz; i++) {
            if (rand() & 1) {
                v1[i] = arg1;
                v2[i] = arg1;
            } else {
                v1[i] = arg2;
                v2[i] = arg2;
            }
        }

        my_vector<T> v3(sz), v4(sz);
        for (size_t i = 0; i < sz; i++) {
            if (rand() & 1) {
                v3[i] = arg1;
                v4[i] = arg2;
            } else {
                v3[i] = arg2;
                v4[i] = arg1;
            }
        }
        
        //equal
        check(v1 == v2, __FILE__, __FUNCTION__, __LINE__);
        check(!(v3 == v4), __FILE__, __FUNCTION__, __LINE__);
        
        //not equal
        check(!(v1 != v2), __FILE__, __FUNCTION__, __LINE__);
        check(v3 != v4, __FILE__, __FUNCTION__, __LINE__);
    }


    static int total;
    static int failed;

    static const int MAX_SIZE = 100000;
};

template<class T>
int test_my_vector_methods<T>::total = 0;

template<class T>
int test_my_vector_methods<T>::failed = 0;

#endif
