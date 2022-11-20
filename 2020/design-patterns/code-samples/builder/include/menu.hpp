#pragma once

#include <iostream>
#include <string>
#include <vector>

class menu {
public:
  void add_item(std::string item) { m_menu_items.push_back(std::move(item)); }
  void render() const noexcept {
    std::cout << "MENU:" << std::endl;
    for (const auto &item : m_menu_items) {
      std::cout << item << std::endl;
    }
    std::cout << std::endl;
  }

private:
  std::vector<std::string> m_menu_items;
};
