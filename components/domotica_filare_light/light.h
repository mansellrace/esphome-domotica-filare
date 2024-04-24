#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/light/light_output.h"

namespace esphome {
namespace domotica_filare {

class DomoticaFilareLight : public light::LightOutput, public Component {
 public:
  void set_stato(GPIOPin *stato) { stato_ = stato; }
  void set_comando(GPIOPin *comando) { comando_ = comando; }

  void setup() override;

  light::LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes({light::ColorMode::ON_OFF});
    return traits;
  }

  void loop();

  void setup_state(light::LightState *state) override;
  void write_state(light::LightState *state) override;

  float get_setup_priority() const { return setup_priority::HARDWARE; }
  float get_loop_priority() const { return 50.0f; }


 protected:
  GPIOPin *stato_;
  GPIOPin *comando_;
  bool pin_stato_precedente;
  uint32_t comando_timer;
  light::LightState *light_state_{nullptr};
};

}  // namespace domotica_filare
}  // namespace esphome
