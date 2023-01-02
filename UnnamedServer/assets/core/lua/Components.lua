local ComponentManager = Core.ECS.ComponentManager
local Type = Core.Type

local PositionComponent = {
    ["Name"] = "Position",
    ["X"] = Type.Float,
    ["Y"] = Type.Float,
    ["Z"] = Type.Float,
}

local RotationComponent = {
    ["Name"] = "Rotation",
    ["X"] = Type.Float,
    ["Y"] = Type.Float,
    ["Z"] = Type.Float,
}

local SizeComponent = {
    ["Name"] = "Size",
    ["X"] = Type.Float,
    ["Y"] = Type.Float,
    ["Z"] = Type.Float,
}

local VelocityComponent = {
    ["Name"] = "Velocity",
    ["X"] = Type.Float,
    ["Y"] = Type.Float,
    ["Z"] = Type.Float,
}

local DefaultComponents = {
    "Position",
    "Rotation",
    "Size",
    "Velocity"
}

ComponentManager:Add(PositionComponent)
ComponentManager:Add(RotationComponent)
ComponentManager:Add(SizeComponent)
ComponentManager:Add(VelocityComponent)
ComponentManager:SetDefaults(DefaultComponents)