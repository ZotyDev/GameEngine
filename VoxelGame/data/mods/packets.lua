Packets = {
	"ConnectRequest" = {
		"Reliability" = false
		"ClientSalt" = "uint64"
	}

	"ConnectChallenge" = {
		"Reliability" = false
		"ServerSalt" = "uint64"
	}

	"ConnectChallengeResponse" = {
		"Reliability" = false
		"ClientServerSalt" = "uint64"
	}

	"ClientDisconnect" = {
		"Reliability" = false
		"ClientServerSalt" = "uint64"
	}

	"ServerDisconnect" = {
		"Reliability" = false
	}

	"UnreliableClientPacket" = {
		"Reliability" = false
		"ClientServerSalt" = "uint64"
		"Data" = "???"
	}

	"UnreliableServerPacket" = {
		"Reliability" = false
		"Data" = "???"
	}

	"ReliableClientPacket" = {
		"Reliability" = true
		"ClientServerSalt" = "uint64"
		"StartingMessageID" = "???"
		"Data" = "???"
	}

	"ReliableServerPacket" = {
		"Reliability" = true
		"StartingMessageID" = "???"
		"Data" = "???"
	}
}

RegisterPacketsLayoyt(Packets)