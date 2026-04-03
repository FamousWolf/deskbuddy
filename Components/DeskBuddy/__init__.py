import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

deskbuddy_component_ns = cg.esphome_ns.namespace("DeskBuddy")
DeskBuddy = deskbuddy_component_ns.class_("DeskBuddy", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DeskBuddy),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)