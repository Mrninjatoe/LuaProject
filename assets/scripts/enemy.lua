posX = 0
posY = 0
vel = 32
health = 2
damage = 1
attackRange = 32
cooldown = 2
userdata = nil
inAttackRange = false
prevDirX = 0
prevDirY = 0

function update(delta)
	if(health <= 0) then
		makeDead(userdata)
	end
	local playerX, playerY = getPlayerPos()
	if(canAttack(playerX, playerY)) then
		attackPlayer(userdata)
	elseif(inAttackRange == false) then
		moveTowardsPlayer(playerX, playerY, delta)
	end
	cooldown = cooldown - 1 * delta
end

function onCollision()

end

function moveTowardsPlayer(playerX, playerY, delta)
	local dirX = (playerX - posX)
	local dirY = (playerY - posY)
	if(dirX < 0) then
		dirX = -1
	elseif(dirX > 0) then
		dirX = 1
	end
	if(dirY < 0) then
		dirY = -1
	elseif(dirY > 0) then
		dirY = 1
	end

	local newPosX = posX + dirX * vel * delta
	if (not doesCollide(posX, posY, newPosX, posY)) then
		posX, posY = move(newPosX, posY, userdata)
	end

	local newPosY = posY + dirY * vel * delta
	if (not doesCollide(posX, posY, posX, newPosY)) then
		posX, posY = move(posX, newPosY, userdata)
	end
end

function canAttack(x, y)
	local tempX = posX - x
	local tempY = posY - y
	distance = math.sqrt(tempX^2 + tempY^2)
	if(distance <= attackRange) then
		inAttackRange = true
		if(cooldown <= 0) then
			cooldown = 2
			return true
		else
			return false
		end
	else
		inAttackRange = false
	end
end

function doesCollide(oldX, oldY, moveX, moveY)
	local positions = getEntitiesAround(oldX, oldY, userdata)
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
