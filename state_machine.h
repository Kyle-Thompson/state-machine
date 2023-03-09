#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <utility>

#include "type_list.h"
#include "validator.h"


template <typename Machine>
class StateMachine {
  static_assert(Validator<Machine>::validate(),
                "enum variant and typelist order mismatch");

  using States = typename Machine::STATES;
  using GlobalState = typename Machine::GLOBAL_STATE;
  using Variants = typename Machine::VARIANTS;
  using LargestType = typename Variants::largest_type;

  constexpr static size_t SIZE = Variants::list_size;
  constexpr static size_t MAX_TYPE_SIZE = sizeof(Variants::largest_type);
  constexpr static auto SEQ = std::make_index_sequence<SIZE>();

 public:
  StateMachine() : current_(static_cast<States>(0)), gstate(buffer_) {
    // default construct the first state
    using FirstType = tl::get_t<0, Variants>;
    std::construct_at<FirstType>(reinterpret_cast<FirstType *>(buffer_));
  }

  template <typename Message>
  void process(const Message &msg) {
    process_impl(msg, SEQ);
  }

 private:
  template <typename Message, size_t... I>
  void process_impl(const Message &msg, std::index_sequence<I...>) {
    (process_individual<Message, I>(msg) || ...);
  }

  template <typename Message, size_t I>
  bool process_individual(const Message &msg) {
    using Type = typename tl::get<I, Variants>::type;

    if (static_cast<int>(current_) == I) {
      // TODO: we should use bit_cast to avoid UB but it seems like bitcast
      // requires the To and From types to have the same size?
      current_ = reinterpret_cast<Type *>(buffer_)->process(msg, &gstate);
      return true;
    } else {
      return false;
    }
  }

  States current_;
  GlobalState gstate;
  alignas(LargestType) std::byte buffer_[sizeof(LargestType)];
};
