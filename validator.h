#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

#include "type_list.h"

template <typename Machine>
struct Validator {
  using States = typename Machine::STATES;
  using Variants = typename Machine::VARIANTS;

  constexpr static bool validate() {
    constexpr auto SIZE = Variants::list_size;
    constexpr auto SEQ = std::make_index_sequence<SIZE>();

    return validate_impl(SEQ);
  }

 private:
  template <size_t I>
  constexpr static bool compare() {
    using Variant = tl::get_t<I, Variants>;

    return static_cast<States>(I) == Variant::STATE;
  }

  template <size_t... I>
  constexpr static bool validate_impl(std::index_sequence<I...>) {
    return (compare<I>() && ...);
  }
};
