--
--  !! WARNING !!
--  DO NOT REQUIRE OR EDIT THIS FILE
--  This is a hack way to make vscode lua lsp plugin understand the functions defined inside the engine
--  (aka, this is what makes autocompletion work)
--

---------------------------------------------------------------------------------
-- Types
---------------------------------------------------------------------------------

---@class Type
Type = {}

Type.Bool           = 0
Type.Char           = 1
Type.Int8           = 2
Type.Int16          = 3
Type.Int32          = 4
Type.Int64          = 5
Type.Uint8          = 6
Type.Uint16         = 7
Type.Uint32         = 8
Type.Uint64         = 9
Type.Float          = 10
Type.Double         = 11
Type.String         = 12

---------------------------------------------------------------------------------
-- ECS
---------------------------------------------------------------------------------

---@class ECS
ECS = {}

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
-- Keyboard Codes
---------------------------------------------------------------------------------

---@class KeyboardCodes
KeyboardCodes = {}

KeyboardCodes.Space			    = 32
KeyboardCodes.Apostrophe		= 39
KeyboardCodes.Comma			    = 44
KeyboardCodes.Minus			    = 45
KeyboardCodes.Period			= 46
KeyboardCodes.Slash			    = 47
KeyboardCodes.D0				= 48
KeyboardCodes.D1				= 49
KeyboardCodes.D2				= 50
KeyboardCodes.D3				= 51
KeyboardCodes.D4				= 52
KeyboardCodes.D5				= 53
KeyboardCodes.D6				= 54
KeyboardCodes.D7				= 55
KeyboardCodes.D8				= 56
KeyboardCodes.D9				= 57
KeyboardCodes.Semicolon		    = 59
KeyboardCodes.Equal			    = 61
KeyboardCodes.A				    = 65
KeyboardCodes.B				    = 66
KeyboardCodes.C				    = 67
KeyboardCodes.D				    = 68
KeyboardCodes.E				    = 69
KeyboardCodes.F				    = 70
KeyboardCodes.G				    = 71
KeyboardCodes.H				    = 72
KeyboardCodes.I				    = 73
KeyboardCodes.J				    = 74
KeyboardCodes.K				    = 75
KeyboardCodes.L				    = 76
KeyboardCodes.M				    = 77
KeyboardCodes.N				    = 78
KeyboardCodes.O				    = 79
KeyboardCodes.P				    = 80
KeyboardCodes.Q				    = 81
KeyboardCodes.R				    = 82
KeyboardCodes.S				    = 83
KeyboardCodes.T				    = 84
KeyboardCodes.U				    = 85
KeyboardCodes.V				    = 86
KeyboardCodes.W				    = 87
KeyboardCodes.X				    = 88
KeyboardCodes.Y				    = 89
KeyboardCodes.Z				    = 90
KeyboardCodes.LeftBracket		= 91
KeyboardCodes.Backslash		    = 92
KeyboardCodes.RightBracket	    = 93
KeyboardCodes.GraveAccent		= 96
KeyboardCodes.World1			= 161
KeyboardCodes.World2			= 162
KeyboardCodes.Escape			= 256
KeyboardCodes.Enter			    = 257
KeyboardCodes.Tab				= 258
KeyboardCodes.Backspace		    = 259
KeyboardCodes.Insert			= 260
KeyboardCodes.Delete			= 261
KeyboardCodes.Right			    = 262
KeyboardCodes.Left			    = 263
KeyboardCodes.Down			    = 264
KeyboardCodes.Up				= 265
KeyboardCodes.PageUp			= 266
KeyboardCodes.PageDown		    = 267
KeyboardCodes.Home			    = 268
KeyboardCodes.End				= 269
KeyboardCodes.CapsLock		    = 280
KeyboardCodes.ScrollLock		= 281
KeyboardCodes.NumLock			= 282
KeyboardCodes.PrintScreen		= 283
KeyboardCodes.Pause			    = 284
KeyboardCodes.F1				= 290
KeyboardCodes.F2				= 291
KeyboardCodes.F3				= 292
KeyboardCodes.F4				= 293
KeyboardCodes.F5				= 294
KeyboardCodes.F6				= 295
KeyboardCodes.F7				= 296
KeyboardCodes.F8				= 297
KeyboardCodes.F9				= 298
KeyboardCodes.F10				= 299
KeyboardCodes.F11				= 300
KeyboardCodes.F12				= 301
KeyboardCodes.F13				= 302
KeyboardCodes.F14				= 303
KeyboardCodes.F15				= 304
KeyboardCodes.F16				= 305
KeyboardCodes.F17				= 306
KeyboardCodes.F18				= 307
KeyboardCodes.F19				= 308
KeyboardCodes.F20				= 309
KeyboardCodes.F21				= 310
KeyboardCodes.F22				= 311
KeyboardCodes.F23				= 312
KeyboardCodes.F24				= 313
KeyboardCodes.F25				= 314
KeyboardCodes.KP0				= 320
KeyboardCodes.KP1				= 321
KeyboardCodes.KP2				= 322
KeyboardCodes.KP3				= 323
KeyboardCodes.KP4				= 324
KeyboardCodes.KP5				= 325
KeyboardCodes.KP6				= 326
KeyboardCodes.KP7				= 327
KeyboardCodes.KP8				= 328
KeyboardCodes.KP9				= 329
KeyboardCodes.KPDecimal		    = 330
KeyboardCodes.KPDivide		    = 331
KeyboardCodes.KPMultiply		= 332
KeyboardCodes.KPSubtract		= 333
KeyboardCodes.KPAdd			    = 334
KeyboardCodes.KPEnter			= 335
KeyboardCodes.KPEqual			= 336
KeyboardCodes.LeftShift		    = 340
KeyboardCodes.LeftControl		= 341
KeyboardCodes.LeftAlt			= 342
KeyboardCodes.LeftSuper		    = 343
KeyboardCodes.RightShift		= 344
KeyboardCodes.RightControl	    = 345
KeyboardCodes.RightAlt		    = 346
KeyboardCodes.RightSuper		= 347
KeyboardCodes.Menu			    = 348

---------------------------------------------------------------------------------
-- Keyboard
---------------------------------------------------------------------------------

---@class Keyboard
---@field Codes KeyboardCodes
Keyboard = {}

---------------------------------------------------------------------------------
-- Mouse Codes
---------------------------------------------------------------------------------

---@class MouseCodes
MouseCodes = {}

MouseCodes.B0			= 0
MouseCodes.B1			= 1
MouseCodes.B2			= 2
MouseCodes.B3			= 3
MouseCodes.B4			= 4
MouseCodes.B5			= 5
MouseCodes.B6			= 6
MouseCodes.B7			= 7
MouseCodes.Left		    = MouseCodes.B0
MouseCodes.Right		= MouseCodes.B1
MouseCodes.Middle		= MouseCodes.B2

---------------------------------------------------------------------------------
-- Mouse
---------------------------------------------------------------------------------

---@class Mouse
---@field Codes MouseCodes
Mouse = {}

---------------------------------------------------------------------------------
-- Gamepad Codes
---------------------------------------------------------------------------------

---@class GamepadCodes
GamepadCodes = {}

GamepadCodes.A                  = 0
GamepadCodes.B                  = 1
GamepadCodes.X                  = 2
GamepadCodes.Y                  = 3
GamepadCodes.LeftBumper			= 4
GamepadCodes.RightBumper		= 5
GamepadCodes.Back				= 6
GamepadCodes.Start				= 7
GamepadCodes.Guide				= 8
GamepadCodes.LeftThumb			= 9
GamepadCodes.RightThumb			= 10
GamepadCodes.DPadUp				= 11
GamepadCodes.DPadRight			= 12
GamepadCodes.DPadDown			= 13
GamepadCodes.DPadLeft			= 14
GamepadCodes.Cross				= GamepadCodes.A
GamepadCodes.Circle				= GamepadCodes.B
GamepadCodes.Square				= GamepadCodes.X
GamepadCodes.Triangle			= GamepadCodes.Y
GamepadCodes.LeftX				= 0
GamepadCodes.LeftY				= 1
GamepadCodes.RightX				= 2
GamepadCodes.RightY				= 3
GamepadCodes.LeftTrigger		= 4
GamepadCodes.RightTrigger		= 5

---------------------------------------------------------------------------------
-- Gamepad
---------------------------------------------------------------------------------

---@class Gamepad
---@field Codes GamepadCodes
Gamepad = {}

---------------------------------------------------------------------------------
-- Input
---------------------------------------------------------------------------------

---@class Input
---@field Keyboard Keyboard
---@field Mouse Mouse
---@field Gamepad Gamepad
Input = {}

---------------------------------------------------------------------------------
-- Core Library
---------------------------------------------------------------------------------

---@class Core
---@field Type Type
---@field Math Math
---@field ECS ECS
---@field Renderer Renderer
---@field Logger Logger
---@field Input Input
Core = {}