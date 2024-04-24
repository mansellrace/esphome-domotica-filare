#include "light.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include <cinttypes>

namespace esphome {
namespace domotica_filare {

void DomoticaFilareLight::setup() {
  this->stato_->setup();
  this->comando_->setup();
  this->comando_->digital_write(false);
  this->comando_timer = 0;
}

void DomoticaFilareLight::loop() {
  if(this->comando_->digital_read()) {
    if (millis() >= this->comando_timer) {
      this->comando_->digital_write(false);
      this->comando_timer = 0;
      if (!this->stato_->digital_read() != this->light_state_->current_values.is_on()) {
        this->light_state_->toggle().perform();
      }
    }
  }
  bool stato_pin = !this->stato_->digital_read();
  bool stato_light = this->light_state_->remote_values.is_on();
  if (this->comando_timer == 0 && (this->pin_stato_precedente != stato_pin)) {
    this->light_state_->toggle().perform();
  }
  this->pin_stato_precedente = stato_pin;
}

void DomoticaFilareLight::setup_state(light::LightState *state) {
  this->light_state_ = state;
}

void DomoticaFilareLight::write_state(light::LightState *state) {
  bool stato_pin = !this->stato_->digital_read();
  bool stato_light = this->light_state_->current_values.is_on();
  if (stato_light != stato_pin) {
    this->comando_->digital_write(true);
    this->comando_timer = millis() + 100;
  }
}

}  // namespace domotica_filare
}  // namespace esphome
