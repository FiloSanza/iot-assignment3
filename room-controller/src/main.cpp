#include <Arduino.h>

#include <components.h>
#include <scheduling.h>
#include <consts.h>

Components::Motor* roller_blinds;
Components::Led* lighting_subsystem;

Tasks::SmartRoom* smart_room;

Scheduling::Scheduler* scheduler = new Scheduling::Scheduler();


void setup() {
  MsgServiceBT.init();
  MsgService.init();
  lighting_subsystem = new Components::Led(LED_PIN);
  roller_blinds = new Components::Motor(SERVO_PIN);
  
  smart_room = new Tasks::SmartRoom(
    lighting_subsystem,
    roller_blinds,
    1000
  );

  smart_room->init();

  scheduler->schedule(smart_room);
}

void loop() {
  scheduler->tick();
}