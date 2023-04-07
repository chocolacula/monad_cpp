#include <functional>
#include <iostream>

#include "type_traits.h"

template <typename InhT>
struct Monad {
  using T = nested_t<InhT>;

  explicit Monad(InhT* inh) : _inh(inh) {
  }

  // monad Interface
  // bind      '>>' | '>>=' 'flatMap'
  // bind_next '<<' | '>>'  'map'

  // Monadic<V> bind(func<Monadic<V>(T)>)
  template <typename F>
  typename std::result_of_t<F(T)>  //
  operator>>(F fn) {
    return InhT::bind_over(_inh, fn);
  }

  template <typename F>
  typename std::result_of_t<F(T)>  //
  bind(F fn) {
    static_assert(is_same_container_v<InhT, std::result_of_t<F(T)>>,
                  "The function should return the same monadic type!");
    return InhT::bind_over(_inh, fn);
  }

  // Monadic<V> bind_next(func<Monadic<V>(_)>)
  template <typename F>
  typename std::result_of_t<F()>  //
  operator<<(F fn) {
    return InhT::bind_next_over(fn);
  }

  template <typename F>
  typename std::result_of_t<F()>  //
  bind_next(F fn) {
    static_assert(is_same_container_v<InhT, std::result_of_t<F()>>,
                  "The function should return the same monadic type!");
    return InhT::bind_next_over(fn);
  }

 private:
  InhT* _inh;
};
