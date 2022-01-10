--local reg = Core.Events.Register
local keycode = Core.Input.Keyboard.Codes
local gamepadcode = Core.Input.Gamepad.Codes
local mousecode = Core.Input.Mouse.Codes

print(keycode.Space)
print(gamepadcode.Cross)
print(mousecode.Middle)

local function OnKeyPressed(key)
    if key == keycode.W then
        
    elseif key == keycode.S then

    elseif key == keycode.A then
        
    elseif key == keycode.D then
        
    elseif key == keycode.E then
        
    elseif key == keycode.Q then
        
    end
end

local function OnKeyReleased(key)
    if key == keycode.W then
        
    elseif key == keycode.S then

    elseif key == keycode.A then
        
    elseif key == keycode.D then
        
    elseif key == keycode.E then
        
    elseif key == keycode.Q then
        
    end
end

--reg.OnKeyPressed(OnKeyPressed)
--reg.OnKeyReleased(OnKeyReleased)