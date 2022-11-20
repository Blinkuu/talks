#include <iostream>

template <typename derived_t> class shape {
public:
  virtual ~shape() = default;

  void render() const noexcept { static_cast<derived_t *>(this)->draw(); }

private:
  shape() = default;
  friend derived_t;
};

class circle : shape<circle> {
public:
  void render() const noexcept { std::cout << "Rendering circle\n"; }
};

class triangle : shape<triangle> {
public:
  void render() const noexcept { std::cout << "Rendering triangle\n"; }
};

/*
class square : shape<triangle> {
public:
  void render() const noexcept { std::cout << "Rendering square\n"; }
};
*/

template <typename shape_t> void draw_shape(const shape_t &shape) {
  shape.render();
}

int main() {
  const circle circleShape{};
  const triangle triangleShape{};
  //  const square squareShape{};

  draw_shape(circleShape);
  draw_shape(triangleShape);
  // draw_shape(squareShape);

  return 0;
}
