#pragma once

#include <memory>

#include "menu.hpp"

class menu_builder {
public:
  menu_builder() : m_menu{std::make_shared<menu>()} {}
  virtual ~menu_builder() = default;

  auto get() noexcept { return m_menu; }

  void reset() noexcept {
    m_menu.reset();
    m_menu = std::make_shared<menu>();
  }

  virtual void produce_checkbox() { m_menu->add_item("Checkbox"); }

  virtual void produce_label() { m_menu->add_item("Label"); }

  virtual void produce_button() { m_menu->add_item("Button"); }

protected:
  std::shared_ptr<menu> m_menu;
};

class dark_menu_builder : public menu_builder {
public:
  virtual void produce_checkbox() override {
    m_menu->add_item("Dark checkbox");
  }

  virtual void produce_label() override { m_menu->add_item("Dark label"); }

  virtual void produce_button() override { m_menu->add_item("Dark button"); }
};
