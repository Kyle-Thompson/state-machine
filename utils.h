#pragma once

#include <type_traits>

template <typename T>
struct strip {
    using type = std::remove_pointer_t<T>;
};

template <typename T>
using strip_t = typename strip<T>::type;
