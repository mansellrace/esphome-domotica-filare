#pragma once

#include "esphome/core/component.h"
#include "esphome/components/mcp23x17_base/mcp23x17_base.h"
#include "esphome/core/hal.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace mcp23017_buffer {

class MCP23017_buffer : public mcp23x17_base::MCP23X17Base, public i2c::I2CDevice {
 public:
  MCP23017_buffer() = default;

  bool digital_read(uint8_t pin) override;
  void setup() override;
  void dump_config() override;
  void loop() override;
  float get_loop_priority() const override;

 protected:
  bool read_reg(uint8_t reg, uint8_t *value) override;
  bool write_reg(uint8_t reg, uint8_t value) override;
  uint8_t buffer_A;
  uint8_t buffer_B;
};

}  // namespace mcp23017_buffer
}  // namespace esphome
