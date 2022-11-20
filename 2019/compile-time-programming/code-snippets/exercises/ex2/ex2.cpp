#include "my_traits.hpp"
#include <cstdint>
#include <iostream>

/* 
 * Zadanie 2/Exercise 2
 * 
 * [PL] Proszę zaimplementować szablony klas oraz zmiennych w taki sposób, aby poniższy program się kompilował.
 *      Proszę NIE korzystać z nagłówka <type_traits>.
 * [EN] Please implement class and variable templates so that the code below compiles.
 *      Please do NOT use <type_traits> header.
 * 
 * [PL] Wskazówka: Jeśli zostanie to zrobione mądrze, kod z pliku my_traits.hpp będzie
 *            można łatwo wykorzystać w późniejszych zadaniach.
 * [EN] Tip: If you do it the smart way, you will be able to reuse my_traits.hpp easily in later exercises.
 */

int main()
{
    using type1 = adv::remove_cv_t<const int>;
    using type2 = adv::remove_cv_t<volatile int>;
    using type3 = adv::remove_cv_t<const volatile int>;
    using type4 = adv::remove_cv_t<const volatile int*>;
    using type5 = adv::remove_cv_t<int * const volatile>;
 
    static_assert(adv::is_same_v<int, type1>);
    static_assert(adv::is_same_v<int, type2>);
    static_assert(adv::is_same_v<int, type3>);
    static_assert(adv::is_same_v<const volatile int*, type4>);
    static_assert(adv::is_same_v<int*, type5>);
}