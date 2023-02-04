#include "red_light.h"

template <>
LightState
RedLight::process(const ChangeLightMsg &msg, GlobalState *gstate) {
  std::cout << "Changing light from red to green" << std::endl;
  return LightState::GREEN;
}
