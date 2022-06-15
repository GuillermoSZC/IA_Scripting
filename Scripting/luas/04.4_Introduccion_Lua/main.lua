-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales
creatures = {}
creaturesPosX = {}
creaturesPosY = {}
creaturesLife = {}
-- Termina tu definicion de variables

function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        creature=addCreature("griphon", mousePositionX-64,  mousePositionY-64)
        table.insert(creatures,0, creature)
        table.insert(creaturesPosX,0, mousePositionX-64)
        table.insert(creaturesPosY,0, mousePositionY-64)
        table.insert(creaturesLife,0, 25)
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    if not down then
    
        -- Escribe tu código para el botón derecho
    for num = 0, #creatures,1 do
        if mousePositionX>creaturesPosX[num] and mousePositionX<creaturesPosX[num]+128 and
        mousePositionY>creaturesPosY[num] and mousePositionY<creaturesPosY[num]+128 then
            creaturesLife[num]=creaturesLife[num]-5
            print(creaturesLife[num])
            if creaturesLife[num]<=0 then        
                removeCreature(creatures[num])
                table.remove(creaturesLife, num)
                table.remove(creaturesPosX, num)
                table.remove(creaturesPosY, num)
                table.remove(creatures, num)
                break
            end
        end
    end
        
        -- Termina tu código
    end
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

