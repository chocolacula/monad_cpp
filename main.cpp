#include <algorithm>
#include <cstring>
#include <iostream>
#include <string_view>
#include <type_traits>
#include <vector>

#include "option.h"

// monadic functions
auto show_m() {
  return [=](auto x) -> Option<decltype(x)> {
    std::cout << "Val " << x << std::endl;
    // like in Haskell 'return' wraps a value to the context
    // because we have explicit return type of the lambda
    return std::move(x);
  };
}

auto filter_m(double treshold) {
  return [=](auto x) { return x < treshold ? Option(x) : None(); };
}

auto div_m(double a) {
  return [=](auto x) { return Option(double(x) / a); };
}

template <typename T>
auto add_m(T a) {
  return [=](auto x) { return Option(x + a); };
}

template <typename T>
auto set_m(T x) {
  return [=]() { return Option(x); };
}

int main() {

  auto a = Option<int>(5);

  std::cout << "Do without Monads" << std::endl;

  a.show().transform([](int x) { return Option((double)x / 2); }).show().filter([](auto x) { return x > 10; }).show();

  std::cout << "Do the same with Monadic lambdas" << std::endl;

  a >> [](int x) { return Option((double)x / 2 + 3); } >> [](auto x) { return x < 10 ? Option(x) : None(); } >>
      show_m();

  std::cout << "Or with Monadic functions" << std::endl;

  a >> div_m(2.0) >> filter_m(10) >> add_m(3.0) >> show_m();

  return 0;
}
