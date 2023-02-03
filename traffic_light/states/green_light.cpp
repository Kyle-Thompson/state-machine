#include "green_light.h"

template <>
LightState GreenLight::process(const ChangeLightMsg &msg, GlobalState *gstate) {
  std::cout << "Changing light from green to yellow" << std::endl;
  return LightState::YELLOW;
}
