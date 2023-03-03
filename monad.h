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
  typename std::enable_if_t<is_same_container_v<InhT, std::result_of_t<F(T)>>, std::result_of_t<F(T)>>
  // SFINAE
  operator>>(F fn) {
    return InhT::bind_over(_inh, fn);
  }

  template <typename F>
  typename std::enable_if_t<is_same_container_v<InhT, std::result_of_t<F(T)>>, std::result_of_t<F(T)>>
  // SFINAE
  bind(F fn) {
    return InhT::bind_over(_inh, fn);
  }

  // Monadic<V> bind_next(func<Monadic<V>(_)>)
  template <typename F>
  typename std::enable_if_t<is_same_container_v<InhT, std::result_of_t<F()>>, std::result_of_t<F()>>
  // SFINAE
  operator<<(F fn) {
    return InhT::bind_next_over(fn);
  }

  template <typename F>
  typename std::enable_if_t<is_same_container_v<InhT, std::result_of_t<F()>>, std::result_of_t<F()>>
  // SFINAE
  bind_next(F fn) {
    return InhT::bind_next_over(fn);
  }

 private:
  InhT* _inh;
};
