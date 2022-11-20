#include <iostream>
#include <memory>
#include <random>

#include "graph.hpp"
#include "visitor.hpp"

struct random {
  static float get() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    return dist(mt);
  }
};

int main() {
  graph city_graph{};

  for (std::size_t i = 0; i < 10; i++) {
    if (random::get() < 0.5f)
      city_graph.add_node(std::make_unique<city_node>(1e6 * random::get()));
    else
      city_graph.add_node(std::make_unique<village_node>(1e6 * random::get()));
  }

  printing_visitor p_visitor{};
  city_graph.accept(p_visitor);

  accumulating_visitor a_visitor{};
  city_graph.accept(a_visitor);

  std::cout << "sum: " << a_visitor.get_sum() << std::endl;

  return 0;
}
