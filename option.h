#include <functional>
#include <iostream>
#include <stdexcept>
#include <type_traits>

#include "monad.h"

struct None {};

template <typename T, typename = std::enable_if_t<std::is_default_constructible_v<T>>>
// SFINAE
class Option : public Monad<Option<T>> {
  T _val;
  bool _is_val;

 public:
  Option(None none)  // NOLINT implicit
      : Monad<Option<T>>(this), _is_val(false) {
  }
  Option(const T& val)  // NOLINT implicit
      : Monad<Option<T>>(this), _is_val(true), _val(val) {
  }
  Option(T&& val)  // NOLINT implicit
      : Monad<Option<T>>(this), _is_val(true), _val(std::move(val)) {
  }

  T& val_safe() {
    if (_is_val) {
      return _val;
    }
    throw std::runtime_error("Option<T> is None");
  }

  bool is_val() {
    return _is_val;
  }
  bool is_none() {
    return !_is_val;
  }

  Option<T> show() {
    if (is_val()) {
      std::cout << "Val " << _val << std::endl;
    } else {
      std::cout << "None" << std::endl;
    }
    return *this;
  }

  Option<T> filter(std::function<bool(T)> fn) {
    if (is_val() && fn(_val)) {
      return *this;
    }
    return None();
  }

  template <typename F>
  typename std::enable_if_t<is_same_container_v<Option<T>, std::result_of_t<F(T)>>, std::result_of_t<F(T)>>
  // SFINAE
  transform(F fn) {
    if (is_val()) {
      return fn(_val);
    }
    return None();
  }

 private:
  friend Monad<Option<T>>;

  template <typename F>
  static typename std::enable_if_t<is_same_container_v<Option<T>, std::result_of_t<F(T)>>, std::result_of_t<F(T)>>
  // SFINAE
  bind_over(Option<T>* self, F fn) {
    // branch with 'Just'
    if (self->is_val()) {
      return fn(self->_val);
    }
    // brunch with 'Nothing'
    return None();
  }

  template <typename F>
  static typename std::enable_if_t<is_same_container_v<Option<T>, std::result_of_t<F()>>, std::result_of_t<F()>>
  // SFINAE
  bind_next_over(F fn) {
    return fn();
  }
};
