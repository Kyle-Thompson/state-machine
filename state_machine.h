#pragma once

#include "validator.h"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <utility>

template <typename Machine> class StateMachine {
  static_assert(Validator<Machine>::validate(),
                "enum variant and tuple order mismatch");

public:
  using States = typename Machine::STATES;
  using GlobalState = typename Machine::GLOBAL_STATE;
  using Variants = typename Machine::VARIANTS;

  StateMachine() : current_(static_cast<States>(0)) {}

  template <typename Message> void process(const Message &msg) {
    constexpr size_t size = std::tuple_size<Variants>{};
    auto seq = std::make_index_sequence<size>();
    process_impl(msg, seq);
  }

private:
  template <typename Message, size_t... I>
  void process_impl(const Message &msg, std::index_sequence<I...>) {
    ([&]() {
      if (current_ == static_cast<States>(I)) {
        current_ = std::get<I>(variants_).process(msg, &gstate);
        return true;
      } else {
        return false;
      }
    }() ||
     ...);
  }

  States current_;
  GlobalState gstate;
  Variants variants_;
};
