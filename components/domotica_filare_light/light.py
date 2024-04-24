from esphome import pins
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_LIGHT_ID
#from .. import domotica_filare_ns

CODEOWNERS = ["@mansellrace"]
#DEPENDENCIES = ["domotica_filare"]

domotica_filare_ns = cg.esphome_ns.namespace("domotica_filare")
DomoticaFilareLight = domotica_filare_ns.class_(
    "DomoticaFilareLight", light.LightOutput, cg.Component
)

CONF_STATO = "stato"
CONF_COMANDO = "comando"
CONFIG_SCHEMA = light.BINARY_LIGHT_SCHEMA.extend(
    {
        cv.GenerateID(CONF_LIGHT_ID): cv.declare_id(DomoticaFilareLight),
        cv.Required(CONF_STATO): pins.gpio_input_pullup_pin_schema,
        cv.Required(CONF_COMANDO): pins.gpio_output_pin_schema,
    }
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_LIGHT_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
    stato = await cg.gpio_pin_expression(config[CONF_STATO])
    comando = await cg.gpio_pin_expression(config[CONF_COMANDO])
    cg.add(var.set_stato(stato))
    cg.add(var.set_comando(comando))