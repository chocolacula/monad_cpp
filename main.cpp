#include <algorithm>
#include <cstring>
#include <iostream>
#include <string_view>
#include <type_traits>
#include <vector>

#include "option.h"
#include "result.h"

template <typename T>
auto show(const Option<T>& m) {
  if (m.is_val()) {
    std::cout << "Val " << m.val() << std::endl;
  } else {
    std::cout << "None" << std::endl;
  }
}

template <typename T, typename E>
auto show(const Result<T, E>& m) {
  if (m.is_val()) {
    std::cout << "Ok " << m.val() << std::endl;
  } else {
    std::cout << "Error " << m.err() << std::endl;
  }
}

// monadic functions
auto filter_m(double treshold) {
  return [=](auto x) { return x < treshold ? Option(x) : None(); };
}

auto div_m(double a) {
  return [=](auto x) -> Option<double> {
    // like in Haskell 'return' wraps a value to the context
    // because we have explicit return type of the lambda
    return double(x) / a;
  };
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
  std::cout << "Use Option<T> and Monadic lambdas" << std::endl;

  auto o = Option<int>(5);

  show(
      o >> [](double x) { return Option(x / 2 + 3); }  //
      >> [](auto x) { return x < 10 ? Option(x) : None(); });

  std::cout << "Or Monadic functions" << std::endl;

  show(o >> div_m(2.0) >> filter_m(10) >> add_m(3.0));

  std::cout << "Use Result<T, E> and Monadic lambdas" << std::endl;

  using R = Result<double, std::string>;
  auto r = R(5);

  show(
      r >> [](double x) { return R(x / 2 + 3); }  //
      >> [](auto x) { return x < 10 ? x : R("x is bigger than 10!"); });

  return 0;
}
