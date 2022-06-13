-- Escribe codigo
require "library"
prepareWindow()

creature = drawCreature(layer, "griphon", 256, 256)
mousePositionX = 0
mousePositionY = 0
changeDirection = false

function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    
    -- Empieza tu código para mover a la criatura
    if onClickLeft(down) == true then
        creaturePositionX = creaturePositionX + 0.4
    else
        creaturePositionX = creaturePositionX - 0.4
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
        if changeDirection == false then
            changeDirection = true
        else
            changeDirection = false
        end
        -- Termina tu código
        
    end
    return changeDirection
end

function onClickRight(down)
    print("Clicked Right")
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

