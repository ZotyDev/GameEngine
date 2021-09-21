local Messages = {
	TextMessage = {
		Reliability = true,
		Data = "string"
	},

	KeyboardInputMessage = {
		Reliability = true,
		KeyCode = "uint16",
		Pressed = "bool"
	},

	MouseInputMessage = {
		Reliability = true,
		KeyCode = "uint16",
		Event = "uint8", -- Moved || Pressed || Released
		X = "uint32",
		Y = "uint32"
	}
}

RegisterMessagesLayout(Messages)

--local MyLogger = Logger.new("Messages")
--MyLogger.Fodase("This is a info text")