#include "texture_factory.hpp"

std::unique_ptr<texture> texture_factory::create(api::rendering current_api) {
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
