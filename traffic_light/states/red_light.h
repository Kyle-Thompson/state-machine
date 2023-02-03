#pragma once

#include <cstdint>
#include <iostream>

#include "../global_state.h"
#include "../messages/change_light.h"
#include "../states.h"

struct RedLight {
  constexpr static LightState STATE = LightState::RED;

  template <typename Msg>
  LightState process(const Msg &msg, GlobalState *gstate);
};
