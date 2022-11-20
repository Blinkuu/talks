#include <iostream>
#include <climits>

template<typename T>
struct remove_const {
    using type = T;
};

template<typename T>
struct remove_const<const T> {
    using type = T;
};

template<typename T>
struct remove_volatile {
    using type = T;
};

template<typename T>
struct remove_volatile<volatile T> {
    using type = T;
};

template<typename T>
struct remove_cv {
    using type = typename remove_const<typename remove_volatile<T>::type>::type;
};

int main() {
    static_assert(std::is_same<int, remove_cv<const volatile int>::type>::value);
}
