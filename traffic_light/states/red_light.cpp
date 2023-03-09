#include "red_light.h"

#include "green_light.h"

#include "../../utils.h"

template <>
LightState
RedLight::process(const ChangeLightMsg &msg, GlobalState *gstate) {
  std::cout << "Changing light from red to green" << std::endl;
  return change_state<GreenLight>(gstate, 4);
}
