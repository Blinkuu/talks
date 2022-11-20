#include <iostream>
#include <memory>

struct api {
  enum class rendering { UNKNOWN = 0, OPENGL, DIRECTX, VULKAN };
};

class texture {
public:
  virtual ~texture() = default;
};

class opengl_texture : public texture {
public:
  opengl_texture() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

class directx_texture : public texture {
public:
  directx_texture() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

class vulkan_texture : public texture {
public:
  vulkan_texture() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

class texture_factory {
public:
  texture_factory() = delete;

  static auto create(api::rendering current_api) -> std::unique_ptr<texture> {
    switch (current_api) {
    case api::rendering::OPENGL:
      return std::make_unique<opengl_texture>();
    case api::rendering::DIRECTX:
      return std::make_unique<directx_texture>();
    case api::rendering::VULKAN:
      return std::make_unique<vulkan_texture>();
    default:
      return nullptr;
    }
  }
};

int main() {
  auto opengl_tex = texture_factory::create(api::rendering::OPENGL);
  auto directx_tex = texture_factory::create(api::rendering::DIRECTX);
  auto vulkan_tex = texture_factory::create(api::rendering::VULKAN);

  return 0;
}
