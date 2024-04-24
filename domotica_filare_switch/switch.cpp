#include "switch.h"
#include "esphome/core/log.h"

namespace esphome {
namespace domotica_filare {

void DomoticaFilareSwitch::setup() {
  this->stato_->setup();
  this->comando_->setup();
  this->comando_->digital_write(false);
  this->comando_timer = 0;
}

void DomoticaFilareSwitch::loop() {
  if(this->comando_->digital_read()) {
    if (millis() >= this->comando_timer) {
      this->comando_->digital_write(false);
    }
  }
  bool stato_pin = !this->stato_->digital_read();
  if (this->state != stato_pin) {
    publish_state(stato_pin);
  }
  // this->pin_stato_precedente = stato_pin;
}

void DomoticaFilareSwitch::write_state(bool state) {
  this->comando_->digital_write(true);
  this->comando_timer = millis() + 500;
}

}  // namespace domotica_filare
}  // namespace esphome
