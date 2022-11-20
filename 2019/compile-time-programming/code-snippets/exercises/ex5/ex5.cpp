#include "texture_factory.hpp"

/*
 * Zadanie 5/Exercise 5
 *
 * [PL] Proszę zaimplementować szablon funkcji, który na podstawie ilości
 * podanych argumentów będzie tworzył odpowiednie instancje klas. Funkcja
 * fabryka powinna zwracać std::unique_ptr.
 *
 * [EN] Please implement a function template, which based on the number of given
 * arguments will instantiate the correct objects. Factory function should
 * return std::unique_ptr.
 *
 *
 * [PL] Wskazówka: Przydatny może okazać się szablon struktury
 * std::is_constructible. [EN] Tip: You may find std::is_constructible very
 * handy.
 */

int main() {
  auto texture_with_filtering = adv::makeTexture("/media/texture1", 1);
  auto texture_without_filtering = adv::makeTexture("/media/texture2");
}
