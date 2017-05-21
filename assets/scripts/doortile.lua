posX = 0
posY = 0

function update(delta)
	local playerX, playerY = getPlayerPos()
	if(playerX < posX + 32 and playerX + 32 > posX
		and playerY < posY + 32 and playerY + 32 > posY) then
		loadNewRoom()
	end
end
