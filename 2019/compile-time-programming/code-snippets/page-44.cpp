#include <type_traits>
#include <iostream>
#include <vector>
#include <array>

template<typename T>
auto get_cont(const T& obj) {
    if constexpr(sizeof(obj) < sizeof(int)) {
        return std::pair{obj, obj};
    } else {
        return std::vector{obj, obj};
    }
}

int main() {
    char x = 5;
    int y = 5;
    
    const std::pair c1 = get_cont(x);
    const std::vector c2 = get_cont(y);
}