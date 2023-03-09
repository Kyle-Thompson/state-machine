#pragma once

#include <utility>

#include "global_state.h"

template <typename StateEnum, typename State>
struct BaseState {
  // TODO: this should be derivable
  // using StateType = decltype(State::STATE);

  template <typename To, typename... Args>
  StateEnum change_state(BaseGlobalState<StateEnum>* gstate,
                         Args&&... args) noexcept {
    return gstate->template change_state<State, To>(
        std::forward<Args>(args)...);
  }
};
