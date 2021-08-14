Info = {
	name = "Developer Mode" -- REQUIRED
	uniqueID = "officialdevelopermode" -- REQUIRED
	version = "1.0.0" -- REQUIRED
	authors = {
		-- The index value that you use is also the role of the specified authors
		"Programmer" = { 
			"ZotyDev"
			-- Specifying more names will make then show bellow the same role
		}
	} -- REQUIRED
	description = "This mod is used to make development easier" -- REQUIRED
	url = "developer.unnamedengine.com" -- OPTIONAL
	credits = "My family and all my friends that supported me" -- OPTIONAL
	tags = {
		"official", "developer", "test", "example"
	}
}

--[[ This part is commented out because it is completely optional (but highly recommended) to have dependencies and compatibility

Dependencies =
{
	-- The dependency name can be anything, but you can't use the same name for two dependencies
	DependencieName = {
		uniqueID = "uniqueidofmod" -- REQUIRED
		required = true -- REQUIRED
		-- The version should always be the minimun version
		version = "1.0.0"
		-- Load order can be:
		-- "BEFORE" - the dependencie should be loaded before the mod
		-- "NONE" - the load order doesn't matter and will not be changed
		-- "AFTER" - the dependencie should be loaded after the mod
		loadOrder = "NONE" -- OPTIONAL (will be set as "NONE" if not included)
	}
}

Compatibility =
{
	{
		uniqueID = "uniqueidofmod" -- REQUIRED
		-- Type can be:
		-- "COMPATIBLE" - the mod is completely compatible
		-- "UNSTABLE" - the mod is somewhat compatible but errors can be found
		-- "INCOMPATIBLE" - the mod is completely incompatible
		type = "COMPATIBLE"
		-- This is a table containing the versions that are affected by this rule
		-- Note: specifying a incomplete versions also works. i.e. '1.0' can be '1.0.0' to '1.0.9' including '1.0.0.n'
		version = 
		{
			"0.9"
			"1.1"
		} -- REQUIRED
		notes = "This is a note that you can use to tell more about the compatibility" -- OPTIONAL
	}
	--]]
}