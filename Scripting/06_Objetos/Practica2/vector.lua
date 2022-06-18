local vector = {}
vector.__index = vector

function new(x,y)
	return setmetatable({x = x or 0, y = y or 0}, vector)
end

local zero = new(0,0)

function vector:__tostring() -- function to print vectors
	return "("..tonumber(self.x)..","..tonumber(self.y)..")"
end

function vector.__add(a,b) -- suma
	return new(a.x+b.x, a.y+b.y)
end

function vector.__sub(a,b) -- resta
	return new(a.x-b.x, a.y-b.y)
end

function vector:mul(num) -- escalar
		return new(num*self.x, num*self.y)
end

function vector:dot(vec) -- dot
    return vec.x*self.x + vec.y*self.y
end

function vector.__div(a,b) -- division
	return new(a.x / b, a.y / b)
end

function vector:len() -- length
	return math.sqrt(self.x * self.x + self.y * self.y)
end

function vector:normalize() -- normalize
	local l = self:len()
	if l > 0 then
		self.x, self.y = self.x / l, self.y / l
	end
	return self
end

