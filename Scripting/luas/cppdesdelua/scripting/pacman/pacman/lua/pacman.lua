
myPacman = pacman.new()
myPacman.setMaxLife(2)
myPacman.setSpeedMultiplier(3)

function setColor(_lives)
	r, g, b = 255, 255, 255
	if _lives == 2 then
		r, g, b = 255, 0, 255
	elseif _lives == 1.5 then
		r, g, b = 0, 255, 255
	elseif _lives == 1 then
		r, g, b = 255, 165, 0
	elseif _lives == 0.5 then
		r, g, b = 0, 255, 0
	elseif _lives == 0 then
		r, g, b = 0, 0, 255
	end
	myPacman.setPowerUpColor(r, g, b)
end