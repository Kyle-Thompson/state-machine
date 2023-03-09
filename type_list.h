#pragma once

#include <algorithm>
#include <cstddef>

template <typename... T>
struct type_list;

namespace tl {

struct invalid_lookup_t;

namespace detail {

template <bool, typename T, typename U>
struct cond {
    using type = T;
};

template <typename T, typename U>
struct cond<false, T, U> {
    using type = U;
};

template <typename T, typename... U>
struct largest_type;

template <typename T>
struct largest_type<T> {
    using type = T;
};

template <typename T, typename U, typename... V>
struct largest_type<T, U, V...> {
    using larger = typename detail::cond<(sizeof(T) > sizeof(U)), T, U>::type;
    using type = typename largest_type<larger, V...>::type;
};

} // namespace detail

template <size_t I, typename... T>
struct get;

template <typename T, typename... U>
struct get<0, type_list<T, U...>> {
    using type = T;
};

template <size_t I, typename T, typename... U>
struct get<I, type_list<T, U...>> {
    using type = typename get<I - 1, type_list<U...>>::type;
};

template <size_t I, typename... T>
using get_t = typename get<I, T...>::type;

// invalid lookup
template <size_t I>
struct get<I> {
    using type = invalid_lookup_t;
};

} // namespace tl

template <typename... T>
struct type_list {
    using largest_type = typename tl::detail::largest_type<T...>::type;
    constexpr static size_t list_size = sizeof...(T);

    constexpr type_list() = default;
};
