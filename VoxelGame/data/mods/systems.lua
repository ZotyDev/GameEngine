local ECS = require("EntityComponentSystem")
local GameTime = require("GameTime")
local Log = require("Log")

local HealthSystem = {
    ["OnAttach"] = function (Entity e)
        ECS.Component(e, "Health")["Points"] = 100
        ECS.Component(e, "Health")["Regeneration"] = 1
    end,

    ["OnUpdate"] = function (Entity e)
        GameTime.SecondsBetween(1)
        ECS.Component(e, "Health")["Points"] = ECS.Component(e, "Health")["Points"] + ECS.Component(e, "Health")["Regeneration"]
    end,

    ["OnDettach"] = function (Entity e)
        Log.info("Removed health component from entity " .. e)
    end,
}