-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil


-- Define tus variables globales
life = {}
index = 0
creature = {}
-- Termina tu definicion de variables

function onUpdate(seconds)

end

function onClickLeft(down)
    index = index + 1
    print("Clicked Left")
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    if not down then
        -- Escribe tu código para el botón izquierdo
        creature[index] = addCreature("griphon", mousePositionX - creatureSizeX * 0.5, mousePositionY - creatureSizeY * 0.5)
        life[index] = 25
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    
    if not down then
        if index > 0 then
            -- Escribe tu código para el botón derecho
            if creature ~= nil then
                posX, posY = getPropPosition(creature[index])
                posX = posX + creatureSizeX * 0.5
                posY = posY + creatureSizeY * 0.5
                
                if mousePositionX == posX and mousePositionY == posY then
                    life[index] = life[index] - 5                    
                    if life[index] == 0 then
                        removeCreature(creature[index])
                        index = index - 1
                    end
                end  
            end         
        end    
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

