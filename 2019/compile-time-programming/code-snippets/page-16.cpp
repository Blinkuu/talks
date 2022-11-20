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

template<typename T>
using remove_cv_t = typename remove_cv<T>::type;

int main() {
    using type_cv= const volatile int;
    
    static_assert(std::is_same_v<int, remove_cv_t<const volatile int>>);
}
