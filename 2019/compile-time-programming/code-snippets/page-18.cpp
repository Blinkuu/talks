#include <iostream>
#include <climits>

template<typename T>
struct type_is {
    using type = T;
};

template<typename T>
using type_is_t = typename type_is<T>::type;

template<typename T>
struct remove_const : type_is<T> {};

template<typename T>
struct remove_const<const T> : type_is<T> {};

template<typename T>
using remove_const_t = typename remove_const<T>::type;

int main() {
    static_assert(std::is_same_v<int, remove_const_t<const int>>);
}
