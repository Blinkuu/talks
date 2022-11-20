#include <array>

constexpr auto fun() {
    auto ptr = new int(5);
    // do something with ptr
    delete ptr;
    return 0;
}

int main() {
    constexpr auto x = fun();
}