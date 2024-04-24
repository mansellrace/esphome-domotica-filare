import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, mcp23xxx_base, mcp23x17_base
from esphome.const import CONF_ID

AUTO_LOAD = ["mcp23x17_base"]
CODEOWNERS = ["@jesserockz, @mansellrace"]
DEPENDENCIES = ["i2c"]
MULTI_CONF = True

mcp23017_buffer_ns = cg.esphome_ns.namespace("mcp23017_buffer")

MCP23017_buffer = mcp23017_buffer_ns.class_("MCP23017_buffer", mcp23x17_base.MCP23X17Base, i2c.I2CDevice)
CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.Required(CONF_ID): cv.declare_id(MCP23017_buffer),
        }
    )
    .extend(mcp23xxx_base.MCP23XXX_CONFIG_SCHEMA)
    .extend(i2c.i2c_device_schema(0x20))
)


async def to_code(config):
    var = await mcp23xxx_base.register_mcp23xxx(config)
    await i2c.register_i2c_device(var, config)
