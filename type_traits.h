#include <type_traits>

template <typename T>
struct nested;

template <template <typename, typename...> typename ContainerT,  //
          typename T, typename... ArgT>
struct nested<ContainerT<T, ArgT...>> {
  using value_type1 = T;
};

template <typename T>
using nested_t1 = typename nested<T>::value_type1;

template <typename T1, typename T2>
struct is_same_container : std::false_type {};

template <template <typename, typename...> typename ContainerT,  //
          typename T1, typename T2, typename... ArgT>
struct is_same_container<ContainerT<T1, ArgT...>, ContainerT<T2, ArgT...>>  //
    : std::true_type {};

template <typename T1, typename T2>
inline constexpr bool is_same_container_v = is_same_container<T1, T2>::value;  // NOLINT
