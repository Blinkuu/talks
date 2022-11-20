#include <iostream>
#include <climits>

template<typename T>
struct type_is {
    using type = T;
};

template<typename T>
using type_is_t = typename type_is<T>::type;

template<bool B, typename T1, typename>
struct conditional : type_is<T1> {};

template<typename T1, typename T2>
struct conditional<false, T1, T2> : type_is<T2> {};

template<bool B, typename T1, typename T2>
using conditional_t = typename conditional<B, T1, T2>::type;

int main() {
    static_assert(std::is_same_v<int, conditional_t<(1 > 0), int, double>>);
    static_assert(std::is_same_v<double, conditional_t<(1 < 0), int, double>>);
}
