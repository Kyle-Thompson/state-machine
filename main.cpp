#include "state_machine.h"
#include "traffic_light/traffic_light.h"

int
main() {
  StateMachine<TrafficLight> state_machine;
  ChangeLightMsg msg;

  state_machine.process(msg);
  state_machine.process(msg);
  state_machine.process(msg);
  state_machine.process(msg);
}
