#pragma once

#include <cstdint>

class city_node;
class village_node;

class visitor {
public:
  virtual void visit(city_node &visitee) = 0;

  virtual void visit(village_node &visitee) = 0;
};

class printing_visitor : public visitor {
  virtual void visit(city_node &visitee) override;

  virtual void visit(village_node &visitee) override;
};

class accumulating_visitor : public visitor {
public:
  [[nodiscard]] uint32_t get_sum() const noexcept;

private:
  virtual void visit(city_node &visitee) override;

  virtual void visit(village_node &visitee) override;

  uint32_t m_sum = 0;
};
