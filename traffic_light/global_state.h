#pragma once

#include <cstddef>

#include "../global_state.h"
#include "states.h"

using BGS = BaseGlobalState<LightState>;

struct GlobalState : BGS {
  GlobalState(std::byte* buf) : BGS(buf) {}
};
