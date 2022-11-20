#include <iostream>
#include <random>
#include <variant>
#include <vector>

struct vec2 {

  std::string get_formatted() {
    return "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
  }

  float x = 0.0f;
  float y = 0.0f;
};

struct circle {
  circle(vec2 position, float radius)
      : m_position{std::move(position)}, m_radius{radius} {}

  void render() {
    printf("Rendering circle at %s with radius %f\n",
           m_position.get_formatted().c_str(), m_radius);
  }

  vec2 m_position;
  float m_radius = 5.0f;
};

struct triangle {
  triangle(vec2 vertexA, vec2 vertexB, vec2 vertexC)
      : m_vertexA{std::move(vertexA)}, m_vertexB{std::move(vertexB)},
        m_vertexC{std::move(vertexC)} {}

  void render() {
    printf("Rendering triangle A = %s, B = %s, C = %s\n",
           m_vertexA.get_formatted().c_str(), m_vertexB.get_formatted().c_str(),
           m_vertexC.get_formatted().c_str());
  }

  vec2 m_vertexA{};
  vec2 m_vertexB{};
  vec2 m_vertexC{};
};

struct call_render {
  void operator()(circle &renderable) { renderable.render(); }

  void operator()(triangle &renderable) { renderable.render(); }
};

struct scene {

  void render() {
    for (auto &node : m_nodes)
      std::visit(call_render{}, node);
  }

  template <typename shape_t> void add_node(shape_t node) {
    m_nodes.push_back(std::move(node));
  }

  std::vector<std::variant<circle, triangle>> m_nodes;
};

struct random {
  static float get() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    return dist(mt);
  }
};

int main() {
  scene s{};

  for (std::size_t i = 0; i < 10; i++) {
    if (random::get() < 0.5f)
      s.add_node(
          circle{{.x = random::get(), .y = random::get()}, random::get()});
    else
      s.add_node(triangle{{.x = random::get(), .y = random::get()},
                          {.x = random::get(), .y = random::get()},
                          {.x = random::get(), .y = random::get()}});
  }

  s.render();

  return 0;
}
