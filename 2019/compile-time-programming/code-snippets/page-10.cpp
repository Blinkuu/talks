#include <iostream>
#include <climits>

template<int X>
struct absolute {
    static_assert(X != INT_MIN);
    static const int value = (X < 0) ? -X : X;
};

int main() {
    const int val0 = absolute<-5>::value;
    const int val1 = absolute<7>::value;

    static_assert(val0 == 5);
    static_assert(val1 == 7);

    std::cout << val0 << "\n";
    std::cout << val1 << "\n";
}
