#include <iostream>
#include <type_traits>

// C++20
template<typename T>
concept Integral = std::is_integral<T>::value;

Integral auto gcd(Integral auto a, Integral auto b){
    if( b == 0 ) return a;
    else return gcd(b, a % b);
}

// C++17
template<typename T, std::enable_if_t<std::is_integral_v<T>>* = nullptr>
auto gcd_old(T a, T b) {
    if( b == 0 ) return a;
    else return gcd(b, a % b);
}

int main() {
    std::cout << gcd(14, 21) << std::endl;
    //std::cout << gcd(14.3, 21.3) << std::endl;

    std::cout << gcd_old(14, 21) << std::endl;
    //std::cout << gcd_old(14.3, 21.3) << std::endl;
}