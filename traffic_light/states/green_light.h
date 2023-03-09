#pragma once

#include <cstdint>
#include <iostream>

#include "../global_state.h"
#include "../messages/change_light.h"
#include "../states.h"

struct GreenLight {
  constexpr static LightState STATE = LightState::GREEN;

  GreenLight() : duration(10) {}
  GreenLight(int duration) : duration(duration) {}
  ~GreenLight() = default;

  template <typename Msg>
  LightState process(const Msg &msg, GlobalState *gstate);

  int duration;
};
