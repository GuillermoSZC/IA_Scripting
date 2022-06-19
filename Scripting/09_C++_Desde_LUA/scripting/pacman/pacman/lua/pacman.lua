cppPacman = pacman.new()
cppPacman.SetMaxLife(1.5)
cppPacman.SetScorePerPowerUp(100)
cppPacman.SetPowerUpSpeedMult(4)
cppPacman.SetPowerUpTime(3)
cppPacman.SetPointsPerCoin(1)
cppPacman.SetPointsToBronzeMedal(2)

function SetColor(_value)
	r ,g ,b = 0, 0, 0	

	if _value == 1.5 then
		r, g, b = 181, 34, 34 --red

	elseif _value == 1 then
		r, g, b = 209, 86, 15 --orange

	elseif _value == 0.5 then
		r, g, b = 17, 209, 23 --green

	elseif _value == 0 then
		r, g, b = 17, 113, 209 --blue
	end

	cppPacman.SetPowerUpColor(r, g, b)
end