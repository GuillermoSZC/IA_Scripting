-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil


-- Define tus variables globales
creaturesArray = {}
life = {}
xPosition = {}
yPosition = {}
-- Termina tu definicion de variables

function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    if not down then
        -- Escribe tu código para el botón izquierdo
        creature = addCreature("griphon", mousePositionX - creatureSizeX * 0.5, mousePositionY - creatureSizeY * 0.5)
        table.insert(creaturesArray, 0, creature)
        table.insert(life, 0, 25) 
        table.insert(xPosition, 0, mousePositionX - creatureSizeX * 0.5)
        table.insert(yPosition, 0, mousePositionY - creatureSizeY * 0.5)        
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
    creatureSizeX, creatureSizeY = getCreatureSize("griphon")
    
    
    if not down then
    -- Escribe tu código para el botón derecho
        for i = 0, #creaturesArray, 1 do
        
            if mousePositionX > xPosition[i] and mousePositionX < xPosition[i] + creatureSizeX
            and mousePositionY > yPosition[i] and mousePositionY < yPosition[i] + creatureSizeY then                
                
                life[i] = life[i] - 5
                print(life[i])
                
                if life[i] <= 0 then
                    removeCreature(creaturesArray[i])
                    table.remove(yPosition, i)   
                    table.remove(xPosition, i)
                    table.remove(life, i)
                    table.remove(creaturesArray, i)
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

