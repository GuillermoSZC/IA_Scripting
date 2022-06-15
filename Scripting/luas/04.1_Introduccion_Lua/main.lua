-- Escribe codigo
require "library"
prepareWindow()

creature = drawCreature(layer, "griphon", 256, 256)
mousePositionX = 0
mousePositionY = 0

    -- Empieza tu código para mover a la criatura
    mov=0
    -- Termina tu código

function onUpdate(seconds)
    creaturePositionX, creaturePositionY = getPropPosition(creature)
    
    -- Empieza tu código para mover a la criatura
if mov==0 then
    creaturePositionX=creaturePositionX-1
end

if mov==1 then
    creaturePositionY=creaturePositionY-1
end

if mov==2 then
    creaturePositionY=creaturePositionY+1
end

if mov==3 then
    creaturePositionX=creaturePositionX+1
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
    if mov==3 then
        mov=0
    else
        mov=mov+1
    end
        -- Termina tu código
    end
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

