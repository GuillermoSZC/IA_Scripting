-- Escribe codigo
require "library"
window_layer = prepareWindow()
require "prepare"

player_health = 50
max_player_health = 200

start_health_bar = 118
end_health_bar = 222

function onUpdate(seconds)
    healthPositionX, healthPositionY = getPropPosition(health_prop)
    -- Empieza tu c�digo
    
    barLenght=222-118
    positionsInBar=barLenght/200;
    
    healthPositionX=positionsInBar*player_health+118
    
    -- Termina tu c�digo
    setPropPosition(health_prop, healthPositionX, healthPositionY)
end

function onClickLeft(down)
    print("Clicked Left")
    if down then
        -- Empieza tu c�digo para bot�n izquierdo
           if player_health>0 then
           player_health=player_health-1
        end
        -- Termina tu c�digo para bot�n izquierdo
    end
end

function onClickRight(down)
    print("Clicked Right")
    if down then
        -- Empieza tu c�digo para bot�n derecho
                   if player_health<200 then
           player_health=player_health+1
        end
        -- Termina tu c�digo para bot�n derecho
    end
end


function onMouseMove(posX, posY)
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()
