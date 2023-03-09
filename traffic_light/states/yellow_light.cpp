#include "yellow_light.h"

#include "red_light.h"

template <>
LightState
YellowLight::process(const ChangeLightMsg &msg, GlobalState *gstate) {
  std::cout << "Changing light from yellow to red" << std::endl;
  return gstate->change_state<decltype(this), RedLight>();
}
