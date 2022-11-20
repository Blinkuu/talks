#include "for_constexpr.hpp"
#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

struct object {
  virtual ~object() = default;
};

template <typename T> struct node : object {
  node(float x, float y) : m_x(x), m_y(y) {}
  void render() const { static_cast<T *>(this)->render(); }

  void print_pos() const {
    std::cout << "pos = [" << m_x << ", " << m_y << "]\n";
  }

  constexpr std::size_t get_id() const noexcept {
    return static_cast<T *>(this)->get_id();
  }

  mutable float m_x;
  mutable float m_y;
};

struct square : node<square> {
  square(float x, float y) : node<square>(x, y) {}

  void render() const {
    // std::cout << "square rendering at ";
    // node<square>::print_pos();
    m_x = 0.0f;
    m_y = 0.0f;
  }

  constexpr std::size_t get_id() const noexcept { return 0u; }
};

struct circle : node<circle> {
  circle(float x, float y) : node<circle>(x, y) {}

  void render() const {
    // std::cout << "circle rendering at ";
    // node<circle>::print_pos();
    m_x = 0.0f;
    m_y = 0.0f;
  }

  constexpr std::size_t get_id() const noexcept { return 1u; }
};

template <typename T> struct type_is { using type = T; };

template <std::size_t type_id> struct get_type : type_is<object> {};
template <> struct get_type<0u> : type_is<square> {};
template <> struct get_type<1u> : type_is<circle> {};

template <std::size_t type_id>
using get_type_t = typename get_type<type_id>::type;

struct Scene {
  void render() {
    for_constexpr<for_bounds<0, 2>>([](auto i) {
      auto id = i;
      using curr_type = typename get_type<id>::type;
      for (const auto &node : m_nodes<curr_type>) {
        node.render();
      }
    });
  }

  template <typename T> void add_node(T node) {
    constexpr auto id = node.get_id();
    using curr_type = typename get_type<id>::type;
    m_nodes<curr_type>.push_back(std::move(node));
  }

  template <typename T> inline static std::vector<T> m_nodes;
  static constexpr std::array<std::size_t, 2> m_type_ids = {0u, 1u};
};

struct random {
  static float get() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    return dist(mt);
  }
};

struct timer {
  using timestamp = std::chrono::time_point<std::chrono::system_clock>;
  using duration = std::chrono::duration<double>;

  static void start() { m_timestamp1 = std::chrono::system_clock::now(); }

  static void stop() {
    m_timestamp2 = std::chrono::system_clock::now();
    m_duration = m_timestamp2 - m_timestamp1;
  }

  static auto read() { return m_duration.count(); }

  inline static timestamp m_timestamp1;
  inline static timestamp m_timestamp2;
  inline static duration m_duration;
};

int main() {
  constexpr std::size_t iter_count = 1e6;

  timer::start();

  Scene scene;
  for (std::size_t i = 0; i < iter_count; i++) {
    const auto random = random::get();
    if (random > 0.5f) {
      scene.add_node(square{random * 10.0f, random * 15.0f});
    } else {
      scene.add_node(circle{random * 30.0f, random * 35.0f});
    }
  }

  scene.render();

  timer::stop();
  std::cout << timer::read() << std::endl;
}
