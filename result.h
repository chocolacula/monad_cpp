#pragma once

#include <stdexcept>
#include <variant>

#include "monad.h"

template <typename T, typename E>
class Result : public Monad<Result<T, E>> {
  std::variant<T, E> _val;

 public:
  Result(const T& val)  // NOLINT implicit
      : _val(val) {
  }
  Result(T&& val)  // NOLINT implicit
      : _val(std::move(val)) {
  }

  Result(const E& err)  // NOLINT implicit
      : _val(err) {
  }
  Result(E&& err)  // NOLINT implicit
      : _val(std::move(err)) {
  }

  const T& val_safe() const {
    auto* p = std::get_if<T>(&_val);
    if (p != nullptr) {
      return *p;
    }
    throw std::runtime_error("Result<T, E> is Error");
  }

  T& val_safe() {
    auto* p = std::get_if<T>(&_val);
    if (p != nullptr) {
      return *p;
    }
    throw std::runtime_error("Result<T, E> is Error");
  }

  const E& err_safe() const {
    auto* p = std::get_if<E>(&_val);
    if (p != nullptr) {
      return *p;
    }
    throw std::runtime_error("Result<T, E> is not Error");
  }

  E& err_safe() {
    auto* p = std::get_if<E>(&_val);
    if (p != nullptr) {
      return *p;
    }
    throw std::runtime_error("Result<T, E> is not Error");
  }

  const T& val() const {
    return std::get<T>(_val);
  }

  T& val() {
    return std::get<T>(_val);
  }

  const E& err() const {
    return std::get<E>(_val);
  }

  E& err() {
    return std::get<E>(_val);
  }

  bool is_val() const {
    return std::holds_alternative<T>(_val);
  }

  bool is_err() const {
    return std::holds_alternative<E>(_val);
  }

 private:
  friend Monad<Result<T, E>>;

  template <typename F>
  typename std::result_of_t<F(T)>  //
  bind_over(F fn) {
    monad_assert<Result<T, E>, F, T>();
    // branch with 'Ok'
    if (is_val()) {
      return fn(std::get<T>(_val));
    }
    // branch with 'Error'
    return E();
  }

  template <typename F>
  static auto bind_next_over(F fn) {
    monad_assert<Result<T, E>, F>();
    return fn();
  }
};
