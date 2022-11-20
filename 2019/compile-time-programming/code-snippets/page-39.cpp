#include <iostream>
#include <climits>

template<int X, int N>
struct pow {
    static const int value = X * pow<X, N - 1>::value;
};

template<int X>
struct pow<X, 0> {
    static const int value = 1;
};

constexpr auto pow_fun(int v, int n) {
    auto result = 1;
    for(std::size_t i = 0; i < n; i++) 
        result *= v;

    return result;
}

int main() {
    const int val1 = pow<2, 8>::value;
    constexpr auto val2 = pow_fun(2, 8);
    static_assert(val1 == 256);
    static_assert(val2 == 256);
    std::cout << val1 << "\n";
    std::cout << val2 << "\n";
}
