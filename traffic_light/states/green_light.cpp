#include "green_light.h"

#include "../../utils.h"

#include "yellow_light.h"

template <>
LightState
GreenLight::process(const ChangeLightMsg &msg, GlobalState *gstate) {
  std::cout << "Changing light from green to yellow after " << duration
            << " seconds.\n";
  return gstate->change_state<strip_t<decltype(this)>, YellowLight>();
}
