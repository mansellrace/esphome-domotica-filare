from esphome import pins
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import CONF_ID

CODEOWNERS = ["@mansellrace"]
#DEPENDENCIES = ["domotica_filare"]

domotica_filare_ns = cg.esphome_ns.namespace("domotica_filare")
DomoticaFilareSwitch = domotica_filare_ns.class_(
    "DomoticaFilareSwitch", switch.Switch, cg.Component
)

CONF_STATO = "stato"
CONF_COMANDO = "comando"  

CONFIG_SCHEMA = (
    switch.switch_schema(DomoticaFilareSwitch)
    .extend(
        {
            cv.GenerateID(CONF_ID): cv.declare_id(DomoticaFilareSwitch),
            cv.Required(CONF_STATO): pins.gpio_input_pullup_pin_schema,
            cv.Required(CONF_COMANDO): pins.gpio_output_pin_schema,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)
    stato = await cg.gpio_pin_expression(config[CONF_STATO])
    comando = await cg.gpio_pin_expression(config[CONF_COMANDO])
    cg.add(var.set_stato(stato))
    cg.add(var.set_comando(comando))
