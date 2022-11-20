#pragma once

#include <iostream>
#include <memory>

class texture {
public:
  virtual ~texture() = default;
  static std::unique_ptr<texture> create();
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
