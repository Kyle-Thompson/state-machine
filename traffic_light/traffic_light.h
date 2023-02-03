#pragma once

#include "global_state.h"
#include "messages/change_light.h"
#include "states.h"
#include "states/green_light.h"
#include "states/red_light.h"
#include "states/yellow_light.h"

struct TrafficLight {
  using GLOBAL_STATE = GlobalState;
  using STATES = LightState;
  using VARIANTS = std::tuple<GreenLight, YellowLight, RedLight>;
};
