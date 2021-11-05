--
--  !! WARNING !!
--  DO NOT REQUIRE OR EDIT THIS FILE
--  This is a hack way to make vscode lua lsp plugin understand the functions defined inside the engine
--  (aka, this is what makes autocompletion work)
--

---------------------------------------------------------------------------------
-- Easing
---------------------------------------------------------------------------------

---@class Easing
Easing = {}

---@param value number
---@return number value
function Easing.EaseInBack(value) end

---@param value number
---@return number value
function Easing.EaseOutBack(value) end

---@param value number
---@return number value
function Easing.EaseInOutBack(value) end

---@param value number
---@return number value
function Easing.EaseInBounce(value) end

---@param value number
---@return number value
function Easing.EaseOutBounce(value) end

---@param value number
---@return number value
function Easing.EaseInOutBounce(value) end

---@param value number
---@return number value
function Easing.EaseInCirc(value) end

---@param value number
---@return number value
function Easing.EaseOutCirc(value) end

---@param value number
---@return number value
function Easing.EaseInOutCirc(value) end

---@param value number
---@return number value
function Easing.EaseInCubic(value) end

---@param value number
---@return number value
function Easing.EaseOutCubic(value) end

---@param value number
---@return number value
function Easing.EaseInOutCubic(value) end

---@param value number
---@return number value
function Easing.EaseInElastic(value) end

---@param value number
---@return number value
function Easing.EaseOutElastic(value) end

---@param value number
---@return number value
function Easing.EaseInOutElastic(value) end

---@param value number
---@return number value
function Easing.EaseInExpo(value) end

---@param value number
---@return number value
function Easing.EaseOutExpo(value) end

---@param value number
---@return number value
function Easing.EaseInOutExpo(value) end

---@param value number
---@return number value
function Easing.EaseInQuad(value) end

---@param value number
---@return number value
function Easing.EaseOutQuad(value) end

---@param value number
---@return number value
function Easing.EaseInOutQuad(value) end

---@param value number
---@return number value
function Easing.EaseInQuart(value) end

---@param value number
---@return number value
function Easing.EaseOutQuart(value) end

---@param value number
---@return number value
function Easing.EaseInOutQuart(value) end

---@param value number
---@return number value
function Easing.EaseInQuint(value) end

---@param value number
---@return number value
function Easing.EaseOutQuint(value) end

---@param value number
---@return number value
function Easing.EaseInOutQuint(value) end

---@param value number
---@return number value
function Easing.EaseInSine(value) end

---@param value number
---@return number value
function Easing.EaseOutSine(value) end

---@param value number
---@return number value
function Easing.EaseInOutSine(value) end

---------------------------------------------------------------------------------
-- Math Library
---------------------------------------------------------------------------------
---@class Math
---@field Easing Easing
Math = {}

---------------------------------------------------------------------------------
-- Core Library
---------------------------------------------------------------------------------

---@class Core
---@field Math Math
Core = {}