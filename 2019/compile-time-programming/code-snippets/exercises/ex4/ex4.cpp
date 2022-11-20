#include "accumulate.hpp"
#include <array>
#include <cstdint>
#include <iostream>

/* 
 * Zadanie 4/Exercise 4
 * 
 * [PL] Proszę zaimplementować szablon funkcji akumulującej, który będzie działał tylko dla liczb typu floating point.
 *      Algorytm ma działać zarówno w czasie kompilacji jak i w czasie wykonania.
 * [EN] Please implement accumulation function template which will only work for floating point numbers.
 *      The algorithm is supposed to work at compile time, as well as runtime.
 * 
 * [PL] Wskazówka: Można korzystać z nagłówka <type_traits>
 * [EN] Tip: You can use <type_traits> header.
 */

int main()
{
    constexpr std::array arr1 { 1.0, 2.0, 3.0, 4.0, 5.0 };
    constexpr std::array arr2 { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
    constexpr std::array arr3 { 1, 2, 3, 4, 5 };

    constexpr auto sum1 = adv::accumulate_floating_point(arr1.begin(), arr1.end());
    constexpr auto sum2 = adv::accumulate_floating_point(arr2.begin(), arr2.end());
    // constexpr auto sum3 = adv::accumulate_floating_point(arr3.begin(), arr3.end()); // Must not compile

    constexpr auto sum = (1.0 + 5.0) * 5.0 / 2.0;
    static_assert(sum1 == sum);
    static_assert(sum2 == sum);
}