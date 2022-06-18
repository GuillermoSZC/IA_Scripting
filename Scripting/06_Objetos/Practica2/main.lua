-- Escribe codigo
require "library"
require "vector"
require "enemy"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

enemies = {}

function onUpdate(seconds)
end

-- Botón izquierdo crea enemigo
function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        enemy = EnemigoHuidizo:new("grunt")
        enemy.id = addCreature(enemy.name, mousePositionX, mousePositionY)
        enemy.posX = mousePositionX
        enemy.posY = mousePositionY
        table.insert(enemies, enemy)
        -- Termina tu código
    end
end

-- Botón derecho quita vida
function onClickRight(down)
    if not down then
        -- Escribe tu código para el botón derecho
        for i = 1, #enemies do
            posX, posY = getPropPosition(enemies[i].id)
            if mousePositionX > posX and mousePositionX < (posX + enemies[i].dimX) 
            and mousePositionY > posY and mousePositionY < (posY + enemies[i].dimY) then
                enemies[i]:receiveDamage(10)
                print(enemies[i].life)
                break
            end
        end
        -- Termina tu código
    end
end

function onMouseMove(posX, posY)
    mousePositionX = posX
    mousePositionY = posY
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end

callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()

