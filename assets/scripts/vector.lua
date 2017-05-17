Vector = {x = 0, y = 0}

function Vector:New(v)
	v = v or {}
	self.__index = self
	setmetatable(v, self)
	return v
end