local ECS = require("EntityComponentSystem")

local Position = {
    ["X"] = ECS.Type("float"),
    ["Y"] = ECS.Type("float"),
    ["Z"] = ECS.Type("float"),
}
ECS.RegisterComponent(Position)

local Rotation = {
    ["X"] = ECS.Type("float"),
    ["Y"] = ECS.Type("float"),
    ["Z"] = ECS.Type("float"),
}
ECS.RegisterComponent(Rotation)

local Velocity = {
    ["X"] = ECS.Type("float"),
    ["Y"] = ECS.Type("float"),
    ["Z"] = ECS.Type("float"),
}
ECS.RegisterComponent(Velocity)

local Sound = {
    ["Source"] = ECS.Type("float"),
}
ECS.RegisterComponent(Sound)

local Name = {
    ["Name"] = ECS.Type("string"),
}
ECS.RegisterComponent(Name)

local Health = {
    ["Points"] = ECS.Type("uint32"),
    ["Regeneration"] = ECS.Type("uint32"),
}
ECS.RegisterComponent(Health)

local Mana = {
    ["Points"] = ECS.Type("uint32"),
    ["Regeneration"] = ECS.Type("uint32"),
}
ECS.RegisterComponent(Mana)

--[[
local Item = {
    ["Type"] = ECS.Type("uint32"),
    ["Amount"] = ECS.Type("uint32"),
}
ECS.RegisterType(Item)

local Inventory = {
    ["ItemArray"] = ECS.ArrayType(20, "Type"),
}
ECS.RegisterComponent(Inventory)
--]]

local Experience = {
    ["Level"] = "uint32",
    ["Current"] = "uint32",
    ["NextLevel"] = "uint32",
}
ECS.RegisterComponent(Experience)

local Hunger = {
    ["Level"] = "uint32",
    ["Required"] = "uint32",
}
ECS.RegisterComponent(Hunger)

local Thirst = {
    ["Level"] = "uint32",
    ["Required"] = "uint32",
}
ECS.RegisterComponent(Thirst)