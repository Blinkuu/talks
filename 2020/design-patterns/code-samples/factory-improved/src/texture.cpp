#include "texture.hpp"

#include "config.hpp"
#include "texture_factory.hpp"

std::unique_ptr<texture> texture::create() {
  return texture_factory::create(config::get().get_rendering_api());
}
