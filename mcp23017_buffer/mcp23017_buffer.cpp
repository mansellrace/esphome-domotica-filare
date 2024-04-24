#include "mcp23017_buffer.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mcp23017_buffer {

static const char *const TAG = "mcp23017";

void MCP23017_buffer::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MCP23017 BUFFER...");
  uint8_t iocon;
  if (!this->read_reg(mcp23x17_base::MCP23X17_IOCONA, &iocon)) {
    this->mark_failed();
    return;
  }

  // Read current output register state
  this->read_reg(mcp23x17_base::MCP23X17_OLATA, &this->olat_a_);
  this->read_reg(mcp23x17_base::MCP23X17_OLATB, &this->olat_b_);

  if (this->open_drain_ints_) {
    // enable open-drain interrupt pins, 3.3V-safe
    this->write_reg(mcp23x17_base::MCP23X17_IOCONA, 0x04);
    this->write_reg(mcp23x17_base::MCP23X17_IOCONB, 0x04);
  }
}

void MCP23017_buffer::dump_config() { ESP_LOGCONFIG(TAG, "MCP23017 buffer: "); }

void MCP23017_buffer::loop() {
  uint8_t value = 0;
  this->read_reg(mcp23x17_base::MCP23X17_GPIOA, &value);
  this->buffer_A = value;
  value = 0;
  this->read_reg(mcp23x17_base::MCP23X17_GPIOB, &value);
  this->buffer_B = value;
}

bool MCP23017_buffer::digital_read(uint8_t pin) {
  uint8_t bit = pin % 8;
  uint8_t buffer = pin < 8 ? this->buffer_A : this->buffer_B;
  return buffer & (1 << bit);
}

bool MCP23017_buffer::read_reg(uint8_t reg, uint8_t *value) {
  if (this->is_failed())
    return false;

  return this->read_byte(reg, value);
}
bool MCP23017_buffer::write_reg(uint8_t reg, uint8_t value) {
  if (this->is_failed())
    return false;

  return this->write_byte(reg, value);
}

float MCP23017_buffer::get_loop_priority() const { return 50.0f; }

}  // namespace mcp23017_buffer
}  // namespace esphome
