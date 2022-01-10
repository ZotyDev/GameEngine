local GraphicsRenderer = {
	["API"] = "OpenGL",
	["Vsync"] = true,
	["FrameLimit"] = 60,
}

local SoundRenderer = {
	["API"] = "OpenAL",
	["Muted"] = false,
	["GeneralVolume"] = 1.0,
}

local CustomKeymaps = {
	["MovementKeymapRetro"] = {
		["Forward"] = "up",
		["Backwards"] = "down",
		["Left"] = "left",
		["Right"] = "right",
	},

	["MovementKeymapModern"] = {
		["Forward"] = "up",
		["Backwards"] = "down",
		["Left"] = "left",
		["Right"] = "right",
	},

	["InteractionKeymapRetro"] = {
		["Accept"] = "z",
		["Cancel"] = "x",
		["Main Menu"] = "esc",
		["Secondary Menu"] = "a",
	},

	["InteractionKeymapModern"] = {
		["Accept"] = "e",
		["Cancel"] = "esc",
		["Main Menu"] = "esc",
		["Seconday Menu"] = "tab",
	},
}

local MouseSensibility = {
	["MouseSensibilityX"] = 1.0,
	["MouseSensibilityY"] = 1.0,
	["MouseScrollSensibilityX"] = 1.0,
	["MouseScrollSensibilityY"] = 1.0,
}