#pragma once

#include <memory>
#include <vector>

#include "visitor.hpp"

class node {
public:
  virtual void accept(visitor &visitor) = 0;
};

class city_node : public node {
public:
  city_node(uint32_t population) : m_population{population} {}

  virtual void accept(visitor &visitor) override { visitor.visit(*this); }

  [[nodiscard]] std::string get_info() const {
    return m_info + " population: " + std::to_string(m_population) +
           " mayor: " + m_mayor + "\n";
  }

  [[nodiscard]] uint32_t get_population() const noexcept {
    return m_population;
  }

private:
  std::string m_info = "city_node";
  uint32_t m_population = 41233921;
  std::string m_mayor = "Mayor Kowalski";
};

class village_node : public node {
public:
  village_node(uint32_t population) : m_population{population} {}

  virtual void accept(visitor &visitor) override { visitor.visit(*this); }

  [[nodiscard]] std::string get_info() const {
    return m_info + " population: " + std::to_string(m_population) + "\n";
  }

  [[nodiscard]] uint32_t get_population() const noexcept {
    return m_population;
  }

private:
  std::string m_info = "village_node";
  uint32_t m_population = 4123;
};

class graph {
public:
  void accept(visitor &visitor) {
    for (auto &node : m_nodes)
      node->accept(visitor);
  }

  void add_node(std::unique_ptr<node> node) {
    m_nodes.push_back(std::move(node));
  }

private:
  std::vector<std::unique_ptr<node>> m_nodes;
};
