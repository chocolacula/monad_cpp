#pragma once

#include <functional>
#include <iostream>

#include "type_traits.h"

template <typename MonadT, typename F, typename... ArgT>
static constexpr void monad_assert() {
  static_assert(is_same_container_v<MonadT, std::result_of_t<F(ArgT...)>>,  //
                "The function should return the same monadic type!");
}

template <typename InhT>
struct Monad {
  using ValueT = nested_t1<InhT>;

  // monad Interface
  // bind      '>>' | '>>=' 'flatMap'
  // bind_next '<<' | '>>'  'map'

  // Monadic<V> bind(func<Monadic<V>(T)>)
  template <typename F>
  typename std::result_of_t<F(ValueT)>  //
  operator>>(F fn) {
    return bind(fn);
  }

  template <typename F>
  typename std::result_of_t<F(ValueT)>  //
  bind(F fn) {
    return derived()->bind_over(fn);
  }

  // Monadic<V> bind_next(func<Monadic<V>(_)>)
  template <typename F>
  typename std::result_of_t<F()>  //
  operator<<(F fn) {
    return bind_next(fn);
  }

  template <typename F>
  typename std::result_of_t<F()>  //
  bind_next(F fn) {
    return derived()->bind_next_over(fn);
  }

 private:
  inline InhT* derived() {
    return static_cast<InhT*>(this);
  }
};
