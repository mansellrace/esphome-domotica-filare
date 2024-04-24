#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/output/binary_output.h"

namespace esphome {
namespace domotica_filare_output {

class DomoticaFilareOutput : public output::BinaryOutput, public Component {
 public:
  void set_stato(GPIOPin *stato) { stato_ = stato; }
  void set_comando(GPIOPin *comando) { comando_ = comando; }

  void setup() override;

  void loop();

  void write_state(bool state) override;

  float get_setup_priority() const { return setup_priority::HARDWARE; }
  float get_loop_priority() const { return 50.0f; }


 protected:
  GPIOPin *stato_;
  GPIOPin *comando_;
  bool pin_stato_precedente;
  bool stato_output;
  uint32_t comando_timer;
};

}  // namespace domotica_filare_output
}  // namespace esphome
