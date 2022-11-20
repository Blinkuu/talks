#include "visitor.hpp"
#include "graph.hpp"

#include <iostream>

void printing_visitor::visit(city_node &visitee) {
  std::cout << visitee.get_info();
}

void printing_visitor::visit(village_node &visitee) {
  std::cout << visitee.get_info();
}

void accumulating_visitor::visit(city_node &visitee) {
  m_sum += visitee.get_population();
}

void accumulating_visitor::visit(village_node &visitee) {
  m_sum += visitee.get_population();
}

uint32_t accumulating_visitor::get_sum() const noexcept { return m_sum; }
