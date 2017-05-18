posX = 0
posY = 0
vel = 3200
userdata = nil
moveReset = 0.05
moveCooldown = 0

function update(delta)
	buttonPressed = getInputs(userdata)
	keyResponse(buttonPressed, delta)
	moveCooldown = moveCooldown - 1 * delta
end

function keyResponse(buttonPressed, delta)
	local newX = posX
	local newY = posY
	if(buttonPressed == 1) then
		newX = posX - vel * delta
		tryMove(newX, newY)
	elseif(buttonPressed == 2) then
		newX = posX + vel * delta
		tryMove(newX, posY)
	elseif(buttonPressed == 3) then
		newY = posY - vel * delta
		tryMove(newX, newY)
	elseif(buttonPressed == 4) then
		newY = posY + vel * delta
		tryMove(newX, newY)
	elseif(buttonPressed == 5) then
		--attack()
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
	if((moveX < 0 or moveX >= 640) or (moveY < 0 or moveY >= 640)) then
		return true
	else
		return false
	end
end