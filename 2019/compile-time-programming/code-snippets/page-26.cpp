#include <type_traits>

template<typename T>
struct type_is {
    using type = T;
};

template<typename T>
using type_is_t = typename type_is<T>::type;

template<bool, typename T = void>
struct enable_if : type_is<T> {};

template<typename T>
struct enable_if<false, T> {};

template<bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <class T, enable_if_t<std::is_integral_v<T>>* = nullptr>
void fun(const T& t) {
    // an implementation for integral types (int, char, unsigned, etc.)
}

template <class T, enable_if_t<std::is_class_v<T>>* = nullptr>
void fun(const T& t) {
    // an implementation for class types
}

int main() {
    int x = 0;
    fun<int>(x);
    
    struct S{} s;
    fun(s);

    int arr[2];
    //fun(arr);
}