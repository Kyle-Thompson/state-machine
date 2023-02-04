#pragma once

#include <cstdint>
#include <iostream>

#include "../global_state.h"
#include "../messages/change_light.h"
#include "../states.h"

struct YellowLight {
  constexpr static LightState STATE = LightState::YELLOW;

  template <typename Msg>
  LightState process(const Msg &msg, GlobalState *gstate);
};
