#include "output.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include <cinttypes>

namespace esphome {
namespace domotica_filare_output {

void DomoticaFilareOutput::setup() {
  this->stato_->setup();
  this->comando_->setup();
  this->comando_->digital_write(false);
  this->comando_timer = 0;
  this->turn_off();
}

void DomoticaFilareOutput::loop() {
  if(this->comando_->digital_read()) {
    if (millis() >= this->comando_timer) {
      this->comando_->digital_write(false);
      this->comando_timer = 0;
    //   if (!this->stato_->digital_read() != this->light_state_->current_values.is_on()) {
    //     this->light_state_->toggle().perform();
    //   }
    }
  }
  bool stato_pin = !this->stato_->digital_read();
  // bool stato_light = this->light_state_->remote_values.is_on();
  // if (this->comando_timer == 0 && (this->pin_stato_precedente != stato_pin)) {
  //   this->light_state_->toggle().perform();
  // }
  // this->pin_stato_precedente = stato_pin;
}

// void DomoticaFilareOutput::setup_state(bool state) {
//   this->light_state_ = state;
// }

void DomoticaFilareOutput::write_state(bool state) {
  bool stato_pin = !this->stato_->digital_read();
  if (state != stato_pin) {
    this->comando_->digital_write(true);
    this->comando_timer = millis() + 100;
  }


}  // namespace domotica_filare_output
}  // namespace esphome
