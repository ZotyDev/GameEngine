--
--  !! WARNING !!
--  DO NOT REQUIRE OR EDIT THIS FILE
--  This is a hack way to make vscode lua lsp plugin understand the functions defined inside the engine
--  (aka, this is what makes autocompletion work)
--

---------------------------------------------------------------------------------
-- Logging
---------------------------------------------------------------------------------

---@class Logger
Logger = {}

---@param name string
---@return Logger logger
function Logger.Create(name) end

---@param name string
---@return Logger logger
function Logger.Get(name) end

---@param msg string
function Logger:Trace(msg) end

---@param msg string
function Logger:Info(msg) end

---@param msg string
function Logger:Warn(msg) end

---@param msg string
function Logger:Error(msg) end

---@param msg string
function Logger:Critical(msg) end

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
-- Framebuffer
---------------------------------------------------------------------------------

---@class Framebuffer
Framebuffer = {}

---@param width integer
---@param height integer
function Framebuffer.Create(width, height) end

---@param index integer 
function Framebuffer:AddColorAttachment(index) end

---@param slot integer
function Framebuffer:AddDepthAttachment(slot) end

---@param width integer
---@param height integer
function Framebuffer:Resize(width, height) end

---------------------------------------------------------------------------------
-- Renderer 2d
---------------------------------------------------------------------------------

---@class Renderer2D
Renderer2D = {}

---------------------------------------------------------------------------------
-- Renderer 3D
---------------------------------------------------------------------------------

---@class Renderer3D
Renderer3D = {}

---------------------------------------------------------------------------------
-- Math Library
---------------------------------------------------------------------------------

---@class Math
---@field Easing Easing
Math = {}

---------------------------------------------------------------------------------
-- Rendering Library
---------------------------------------------------------------------------------

---@class Renderer
---@field Framebuffer Framebuffer
---@field Renderer2D Renderer2D
---@field Renderer3D Renderer3D
Renderer = {}

---------------------------------------------------------------------------------
-- Core Library
---------------------------------------------------------------------------------

---@class Core
---@field Math Math
---@field Renderer Renderer
---@field Logger Logger
Core = {}