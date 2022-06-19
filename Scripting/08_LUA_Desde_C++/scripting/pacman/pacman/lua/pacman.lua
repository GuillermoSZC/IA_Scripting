scorePerPowerUp = 100
powerUpTime = 3
powerUpSpeedMult = 4
powerUpColor = { 255, 0, 255 }
pointsToBronzeMedal = 2
pointsPerCoin = 1

function SetColor(_value)

	if _value == 1.5 then
		return 181, 34, 34 --red

	elseif _value == 1 then
		return 209, 86, 15 --orange

	elseif _value == 0.5 then
		return 17, 209, 23 --green

	elseif _value == 0 then
		return 17, 113, 209 --blue
	end

	return 0, 0, 0

end