#include <Arduino.h>

#include <components.h>
#include <scheduling.h>
#include <consts.h>

Components::Motor* roller_blinds;
Components::Led* lighting_subsystem;

Tasks::SmartRoom* smart_room;

MsgServiceBT* msg_serviceBT;
Scheduling::Scheduler* scheduler = new Scheduling::Scheduler();

void setup() {
  msg_serviceBT = new MsgServiceBT(RX_PIN, TX_PIN);
  MsgService.init();
  lighting_subsystem = new Components::Led(LED_PIN);
  roller_blinds = new Components::Motor(SERVO_PIN);


  smart_room = new Tasks::SmartRoom(
    lighting_subsystem,
    roller_blinds,
    msg_serviceBT,
    1000
  );

  smart_room->init();

  scheduler->schedule(smart_room);
}

void loop() {
  scheduler->tick();
}