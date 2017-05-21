posX = 0
posY = 0
vel = 256
userdata = nil
moveReset = 1
attackCooldown = 0
attackRange = 42
health = 0
damage = 0

function band(a, b)
	return a & b
end

function update(delta)
	if(health <= 0) then
		makeDead(userdata)
	end
	buttonPressed = getInputs(userdata)
	keyResponse(buttonPressed, delta)
	attackCooldown = attackCooldown - 1 * delta
end

function keyResponse(buttonBitMap, delta)
	local newX = posX
	local newY = posY
	local prevDirX = 0
	local prevDirY = 0

	if(band(buttonBitMap, 1) ~= 0) then
		newX = posX - vel * delta
		prevDirX = -1
		tryMove(newX, newY)
	end

	if(band(buttonBitMap, 2) ~= 0) then
		newX = posX + vel * delta
		prevDirX = 1
		tryMove(newX, posY)
	end

	if(band(buttonBitMap, 4) ~= 0) then
		newY = posY - vel * delta
		prevDirY = -1
		tryMove(newX, newY)
	end

	if(band(buttonBitMap, 8) ~= 0) then
		newY = posY + vel * delta
		prevDirY = 1
		tryMove(newX, newY)
	end

	if(band(buttonBitMap, 16) ~= 0 and attackCooldown <= 0) then
		attack(userdata, prevDirX, prevDirY, attackRange)
		attackCooldown = moveReset
	end
end

function tryMove(x, y)
	if(doesCollide(posX, posY, x, y) == false) then
		posX, posY = move(x, y, userdata)
	end
end

function onCollision()

end

function doesCollide(oldX, oldY, moveX, moveY)
	positions = getEntitiesAround(oldX, oldY)
	i = 0
	while(positions[i] ~= nil) do
		if(moveX < positions[i] + 32 and moveX + 32 > positions[i]
		and moveY < positions[i + 1] + 32 and moveY + 32 > positions[i + 1]) then
			return true
		end
		i = i + 2
	end
	if((moveX < 0 or moveX >= 608) or (moveY < 0 or moveY >= 608)) then
		return true
	else
		return false
	end
end
