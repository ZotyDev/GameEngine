local ECS = require('ECS')

local HealthComponent = {}
HealthComponent["HealthPoints"] = "int"
HealthComponent["Regeneration"] = "float"

ECS.RegisterComponent("Health", HealthComponent)