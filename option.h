#pragma once

#include <stdexcept>

#include "monad.h"

struct None {};

template <typename T, typename = std::enable_if_t<std::is_default_constructible_v<T>>>
// SFINAE
class Option : public Monad<Option<T>> {
  T _val;
  bool _is_val;

 public:
  Option(None none)  // NOLINT implicit
      : _is_val(false) {
  }
  Option(const T& val)  // NOLINT implicit
      : _is_val(true), _val(val) {
  }
  Option(T&& val)  // NOLINT implicit
      : _is_val(true), _val(std::move(val)) {
  }

  const T& val_safe() const {
    if (_is_val) {
      return _val;
    }
    throw std::runtime_error("Option<T> is None");
  }

  T& val_safe() {
    if (_is_val) {
      return _val;
    }
    throw std::runtime_error("Option<T> is None");
  }

  const T& val() const {
    return _val;
  }

  T& val() {
    return _val;
  }

  bool is_val() const {
    return _is_val;
  }

  bool is_none() const {
    return !_is_val;
  }

 private:
  friend Monad<Option<T>>;

  template <typename F>
  typename std::result_of_t<F(T)>  //
  bind_over(F fn) {
    monad_assert<Option<T>, F, T>();
    // branch with 'Just'
    if (is_val()) {
      return fn(_val);
    }
    // brunch with 'Nothing'
    return None();
  }

  template <typename F>
  static auto bind_next_over(F fn) {
    monad_assert<Option<T>, F>();
    return fn();
  }
};
