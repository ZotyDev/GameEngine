local Ingredient = require("data.mods.fantasy.src.alchemy.Ingredient")

local IngredientActions = {}

local GrinderResult = {
    ["pieces"] = "powder",
}

local DryerResult = {
    ["soft"] = "dried",
}

local BurnerResult = {
    ["soft"] = "ashes",
    ["pieces"] = "scorched",
}

local HammerResult = {
    ["solid"] = "pieces",
    ["soft"] = "ground",
}

local EnchanterResult = {
    ["soft"] = "animated",
    ["meta"] = "magical"
}

function IngredientActions.Grind(ingredient)
    local state = ingredient.state
    ingredient.state = GrinderResult[state] or state
end

function IngredientActions.Dry(ingredient)
    local state = ingredient.state
    ingredient.state = DryerResult[state] or state
end

function IngredientActions.Burn(ingredient)
    local state = ingredient.state
    ingredient.state = BurnerResult[state] or state
end

function IngredientActions.Hammer(ingredient)
    local state = ingredient.state
    ingredient.state = HammerResult[state] or state
end

function IngredientActions.Enchant(ingredient)
    local state = ingredient.state
    ingredient.state = EnchanterResult[state] or state
end

return IngredientActions