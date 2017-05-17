posX = 32
posY = 0

function update(delta)
	
end

function move(x, y)
	if(doesCollide(posX, posY, x, y)) then
		return posX, posY
	else
		posX = posX + x
		posY = posY + y
		return posX, posY
	end
end

function onCollision()
	
end

function doesCollide(oldX, oldY, moveX, moveY)
	positions = getEntitiesAround(oldX, oldY)
	local newX = oldX + moveX
	local newY = oldY + moveY
	i = 0
	while(positions[i] ~= nil) do
		if(positions[i] == newX and positions[i + 1] == newY) then
			return true
		end
		i = i + 2
	end
	if((newX < 0 or newX >= 640) or (newY < 0 or newY >= 640)) then
		return true
	else
		return false
	end
end