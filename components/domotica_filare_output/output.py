from esphome import pins
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID

CODEOWNERS = ["@mansellrace"]

domotica_filare_output_ns = cg.esphome_ns.namespace("domotica_filare_output")
DomoticaFilareOutput = domotica_filare_output_ns.class_("DomoticaFilareOutput", cg.Component, output.BinaryOutput,)

CONF_STATO = "stato"
CONF_COMANDO = "comando"
CONFIG_SCHEMA = cv.All(
    output.BINARY_OUTPUT_SCHEMA.extend(
        {
            cv.Required(CONF_ID): cv.declare_id(DomoticaFilareOutput),
            cv.Required(CONF_STATO): pins.gpio_input_pullup_pin_schema,
            cv.Required(CONF_COMANDO): pins.gpio_output_pin_schema,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await output.register_output(var, config)
    await cg.register_component(var, config)
    stato = await cg.gpio_pin_expression(config[CONF_STATO])
    comando = await cg.gpio_pin_expression(config[CONF_COMANDO])
    cg.add(var.set_stato(stato))
    cg.add(var.set_comando(comando))