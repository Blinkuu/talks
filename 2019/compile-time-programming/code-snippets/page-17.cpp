#include <iostream>
#include <climits>

template<typename T>
struct type_is {
    using type = T;
};

template<typename T>
using type_is_t = typename type_is<T>::type;



int main() {
    static_assert(std::is_same_v<int, type_is_t<int>>);
}
