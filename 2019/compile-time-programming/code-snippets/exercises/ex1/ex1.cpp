#include "my_traits.hpp"
#include <cstdint>

/* 
 * Zadanie 1/Exercise 1
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
    static_assert(adv::is_same_v<double, double>);
    static_assert(adv::is_same_v<int, std::int32_t>);
    static_assert(not adv::is_same_v<float, double>);
}