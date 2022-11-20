#pragma once

#include "api.hpp"

class config {
public:
  static config &get() {
    static config my_config{};

    return my_config;
  }

  auto get_rendering_api() const noexcept { return m_rendering_api; }

private:
  config() = default;

  api::rendering m_rendering_api = api::rendering::VULKAN;
};
