posX = 0
posY = 0
attackRange = 32
cooldown = 2
userdata = nil

function update(delta)
	local playerX, playerY = getPlayerPos()
	if(canAttack(playerX, playerY)) then
		print("attacking player")
	end
	if(canMove()) then
		moveTowardsPlayer(playerX, playerY)
	end
	cooldown = cooldown - 1 * delta
end

function onCollision()
	
end

function moveTowardsPlayer(playerX, playerY)
	dirX = (playerX - posX)
	dirY = (playerY - posY)
	if(dirX < 0) then
		dirX = dirX / (dirX * -1)
	elseif(dirX > 0) then
		dirX = dirX / dirX
	end
	if(dirY < 0) then
		dirY = dirY / (dirY * -1)
	elseif(dirY > 0) then
		dirY = dirY / dirY
	end
	dirX = dirX * 32
	dirY = dirY * 32
	print(dirX, dirY)
	if(doesCollide(posX, posY, dirX, dirY) == false) then
		posX, posY = move(dirX, dirY, userdata)
	end
end

function canAttack(x, y)
	local tempX = posX - x
	local tempY = posY - y
	distance = math.sqrt(tempX^2 + tempY^2)
	if(distance <= attackRange) then
		cooldown = 2
		return true
	else
		return false
	end
end

function canMove()
	if(cooldown <= 0) then
		cooldown = 2
		return true
	else
		return false
	end
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
