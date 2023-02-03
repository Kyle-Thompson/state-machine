#include "state_machine.h"
#include "traffic_light/traffic_light.h"

int main() {
  /* StateMachine<GlobalState, LightState, GreenLight, YellowLight, RedLight> */
  /*     state_machine; */
  StateMachine<TrafficLight> state_machine;
  ChangeLightMsg msg;

  state_machine.process(msg);
  state_machine.process(msg);
  state_machine.process(msg);
  state_machine.process(msg);
}
