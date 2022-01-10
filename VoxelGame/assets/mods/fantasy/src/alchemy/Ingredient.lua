local Ingredient = {}
Ingredient.__index = Ingredient

setmetatable(Ingredient, {
    __call = function(cls, ...)
        return cls.new(...)
    end
})

function Ingredient.new(name, state, type)
    local self = setmetatable({}, Ingredient)
    self.name = name
    self.state = state
    self.type = type
    return self
end

function Ingredient:SetName(name)
    self.name = name
end

function Ingredient:GetName()
    return self.name
end

function Ingredient:SetType(type)
    self.type = type
end

function Ingredient:GetType()
    return self.type
end

function Ingredient:SetState(state)
    self.state = state
end

function Ingredient:GetState()
    return self.state
end

return Ingredient