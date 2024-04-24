#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/automation.h"
#include "esphome/components/switch/switch.h"


namespace esphome {
namespace domotica_filare {

class DomoticaFilareSwitch : public switch_::Switch, public Component {
 public:
  //DomoticaFilareSwitch();
  void set_stato(GPIOPin *stato) { stato_ = stato; }
  void set_comando(GPIOPin *comando) { comando_ = comando; }

  void setup() override;
  void loop() override;

  Trigger<> *get_turn_on_trigger() const;
  Trigger<> *get_turn_off_trigger() const;
  void set_optimistic(bool optimistic);
  void set_assumed_state(bool assumed_state);

  //float get_setup_priority() const override;

 protected:
  //bool assumed_state() override;

  void write_state(bool state) override;
  GPIOPin *stato_;
  GPIOPin *comando_;
  bool pin_stato_precedente;
  bool stato_attuale;
  uint32_t comando_timer;
  Trigger<> *turn_on_trigger_;
  Trigger<> *turn_off_trigger_;
  Trigger<> *prev_trigger_{nullptr};
};

}  // namespace domotica_filare
}  // namespace esphome
