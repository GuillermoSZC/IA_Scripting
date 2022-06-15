--width = 300
--coin_score = 50

--function getWidth()
--	return 200
--end

scorePowerUp = 10000
timePowerUp = 7
speedMultiplier = 3
powerUpColor = { 0, 0, 255}
pointsToBronze = 200
pointsPerCoin = 100

function setColor(_lives)
	if _lives == 1.5 then
		return 255, 0, 0
	elseif _lives == 1 then
		return 255, 165, 0
	elseif _lives == 0.5 then
		return 0, 255, 0
	elseif _lives == 0 then
		return 0, 0, 255
	end
	return 255, 255, 255
end