#include <type_traits>

namespace detail {
    template <class T> char test(int T::*);
    struct two { char c[2]; };
    template <class T> two test(...);
}
 
template <class T>
struct is_class : std::integral_constant<bool, sizeof(detail::test<T>(0))==1
                                            && !std::is_union<T>::value> {};

struct S {};

int main() {
    static_assert(true == is_class<S>::value);
    static_assert(false == is_class<int>::value);
}