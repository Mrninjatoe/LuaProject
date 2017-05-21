amountOfEnemies = 1
playerIsDead = false
userdata = nil
doorPosX = nil
doorPosY = nil

function update(delta)
	if(playerIsDead == true) then
		endGame()
	end
	if(amountOfEnemies == 0) then
		doorPosX, doorPosY = spawnDoor(userdata)
	end
	
end