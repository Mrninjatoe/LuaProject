amountOfEnemies = 0
playerIsDead = false

function update(delta)
	if(playerIsDead == true) then
		endGame()
	end
	if(amountOfEnemies == 0) then
		spawnDoor()
	end
end