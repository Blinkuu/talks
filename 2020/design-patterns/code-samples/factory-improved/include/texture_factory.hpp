#pragma once

#include <memory>

#include "api.hpp"
#include "texture.hpp"

class texture;

class texture_factory {
public:
  texture_factory() = delete;
  static std::unique_ptr<texture> create(api::rendering current_api);
};
