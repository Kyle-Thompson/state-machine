#pragma once

#include <cstdint>
#include <iostream>

#include "../global_state.h"
#include "../messages/change_light.h"
#include "../states.h"
#include "../../base_state.h"

struct RedLight : BaseState<LightState, RedLight> {
  constexpr static LightState STATE = LightState::RED;

  RedLight() = default;
  ~RedLight() = default;

  template <typename Msg>
  LightState process(const Msg &msg, GlobalState *gstate);
};
