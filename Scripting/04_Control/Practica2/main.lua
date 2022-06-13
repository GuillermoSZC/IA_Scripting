-- Escribe codigo
require "library"
prepareWindow()

creature = drawCreature(layer, "griphon", 256, 256)
mousePositionX = 0
mousePositionY = 0
changeDirection = 0

function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    
    -- Empieza tu código para mover a la criatura
    if onClickLeft(down) == 0 then
        creaturePositionX = creaturePositionX + 10 * seconds
        print("right")        
    elseif onClickLeft(down) == 1 then 
        creaturePositionX = creaturePositionX - 10 * seconds
        print("left")
    elseif onClickLeft(down) == 2 then 
        creaturePositionY = creaturePositionY - 10 * seconds
        print("up")
    elseif onClickLeft(down) == 3 then 
        creaturePositionY = creaturePositionY + 10 * seconds
        print("down")
    end
    -- Termina tu código

    setPropPosition(creature, creaturePositionX, creaturePositionY)
end

function onClickLeft(down)
    if down then
        print("Clicked Left")
        creatureSizeX, creatureSizeY = getCreatureSize("griphon")
        creaturePositionX, creaturePositionY = getPropPosition(creature)
        
        -- Escribe tu código aqui para botón izquierdo ratón
        if changeDirection < 3 then
            changeDirection = changeDirection + 1
        else
            changeDirection = 0
        end
        -- Termina tu código
        
    end
    return changeDirection
end

function onClickRight(down)
    print("Clicked right")
end

function onMouseMove(posX, posY)
    mousePositionX = posX
    mousePositionY = posY
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()

