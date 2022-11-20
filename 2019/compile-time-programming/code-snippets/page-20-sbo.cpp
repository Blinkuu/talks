#include <climits>
#include <iostream>
#include <type_traits>

template <typename T> struct type_is { using type = T; };

template <typename T> using type_is_t = typename type_is<T>::type;

template <bool, typename T1, typename> struct conditional : type_is<T1> {};

template <typename T1, typename T2>
struct conditional<false, T1, T2> : type_is<T2> {};

template <bool B, typename T1, typename T2>
using conditional_t = typename conditional<B, T1, T2>::type;

struct string {

  template <typename T, std::size_t N> string(T (&buffer)[N]) {
    static_assert(std::is_same_v<const char, T>);
    conditional_t<(N < 16), init_sbo, init>{}(*this, buffer, N);
  }

  ~string() {
    if (_size > 16) {
      delete[] _data._begin;
    }
  }

  struct init_sbo {
    void operator()(string &s, const char *buff, std::size_t n) {
      std::cout << "Small buffer optimization" << std::endl;
      s._size = n;
      s._capacity = n;
      for (std::size_t i = 0; i < n; ++i) {
        s._data._buffer[i] = buff[i];
      }
    }
  };

  struct init {
    void operator()(string &s, const char *buff, std::size_t n) {
      std::cout << "Allocating memory" << std::endl;
      s._data._begin = new char[n];
      s._size = n;
      s._capacity = n;
      for (std::size_t i = 0; i < n; ++i) {
        s._data._begin[i] = buff[i];
      }
    }
  };

  union {
    char _buffer[16];
    char *_begin;
  } _data;

  std::size_t _size;
  std::size_t _capacity;
};

int main() {
  string s1("hell");
  string s2("hellwiudjdwaonbdowiandwoiandwoia");
}
