#include <iostream>
#include <cstddef>
#include <cstring>
#include "my_array.h"

using std::cout;
using std::size_t;
using std::ostream;

template<typename T, size_t N>
ostream& operator<<(ostream& stream, my_array<T, N> array) {
    for (size_t i = 0; i < N; i++)
        stream << array[i];
    return stream;
}

template<typename T, size_t N>
void test_core() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.empty();
    ca.empty();
    a.size();
    ca.size();

    a.at(0);
    ca.at(0);
    a[0];
    ca[0];
    (void)static_cast<const T&>(a[0]);
    (void)static_cast<const T&>(ca[0]);
}

template<typename T, size_t N>
void test_assign() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.fill(T());

    a[0] = T();

    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            a[i] = a[j];
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            a[i] = ca[j];
}

template<size_t N>
void test_bool() {
    my_array<bool, N> a;
    a.fill(0);
    cout << a << '\n';
    a.fill(1);
    cout << a << '\n';
    cout << '\n';

    srand(13);
    for (size_t i = 0; i < N; i++) {
        bool value = rand() & 1;
        cout << value;
        a[i] = value;
    }
    cout << '\n' << a << '\n';
    cout << '\n';

    for (size_t i = 0; i < N / 2; i++)
        a[i] = a[i + N / 2];
    cout << a << '\n';
 
    
    a[0] = (a[0] ? 0 : 1);
    const my_array<bool, N> &ca = a;
    for (size_t i = 0; i < N / 2; i++)
        a[i + N / 2] = ca[i];
    cout << a << '\n';
    
}

class NonCopyable {
  public:
    NonCopyable() {}
  private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable);
};

class MyClass {
  public:
    MyClass(const char* str = "Hello world!") :
            str(str) {
    }
    const char* str;
};

int main() {
    test_core<int, 10>();
    test_core<bool, 10>();
    test_core<NonCopyable, 10>();

    test_assign<int, 10>();
    test_assign<bool, 10>();

    test_bool<32>();

    my_array<MyClass, 10> a;
    my_array<MyClass, 10> b;
    b.fill(MyClass("Hi!"));

    cout << a[0].str << '\n' << b[0].str << '\n';
    a = b;
    cout << a[0].str << '\n';

    return 0;
}
