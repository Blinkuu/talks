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

int main() {
    static_assert(std::is_same<int, remove_const<const int>::type>::value);
}
