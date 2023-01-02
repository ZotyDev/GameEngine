
local MaterialManager = Core.Renderer.MaterialManager
local Type = Core.Type

local Sprite = {
    ["Name"] = "Sprite",
    ["Color"] = Type.Vec4,
    ["Texutre"] = Type.Texture2D,
}

MaterialManager:Add(Sprite)