#include <iostream>
#include <memory>

#include "menu_builder.hpp"

int main() {

  menu_builder builder{};
  builder.produce_label();
  builder.produce_button();
  builder.produce_button();
  builder.produce_checkbox();

  const auto menu1 = builder.get();
  const auto menu2 = builder.get();
  menu1->render();
  menu2->render();

  builder.reset();

  builder.produce_label();
  builder.produce_checkbox();
  const auto menu3 = builder.get();
  menu3->render();

  dark_menu_builder dark_builder{};
  dark_builder.produce_label();
  dark_builder.produce_button();
  dark_builder.produce_button();
  dark_builder.produce_checkbox();

  const auto dark_menu1 = dark_builder.get();
  dark_menu1->render();

  return 0;
}
