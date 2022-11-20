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

int main() {
    const int val = pow<2, 8>::value;
    static_assert(val == 256);
    std::cout << val<< "\n";
}
