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
  constexpr static size_t SIZE = std::tuple_size<Variants>{};
  constexpr static auto SEQ = std::make_index_sequence<SIZE>();

  StateMachine() : current_(static_cast<States>(0)) {}

  template <typename Message> void process(const Message &msg) {
    process_impl(msg, SEQ);
  }

private:
  template <typename Message, size_t... I>
  void process_impl(const Message &msg, std::index_sequence<I...>) {
    (process_individual<Message, I>(msg) || ...);
  }

  template <typename Message, size_t I>
  bool process_individual(const Message &msg) {
    if (current_ == static_cast<States>(I)) {
      current_ = std::get<I>(variants_).process(msg, &gstate);
      return true;
    } else {
      return false;
    }
  }

  States current_;
  GlobalState gstate;
  Variants variants_;
};
