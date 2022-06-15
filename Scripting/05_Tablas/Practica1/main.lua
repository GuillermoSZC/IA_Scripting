-- Escribe codigo
require "library"
require "prepare"

-- Define tus variables globales
xPosition = 450
yPosition = 330
-- Termina tu definicion de variables

function pintarPunto(xPosition, yPosition)
    -- Rellenar código para pintar un punto en la pantalla
    drawPoint(xPosition, yPosition)
    -- Fin de código
end

function onUpdate(seconds)
    onDraw()
end

function onDraw()
    -- Empieza tu código, que debe emplear la funcion pintarPunto
    for i = 0, 100, 1 do -- x quad Size
        for j = 0, 100, 1 do -- y quad Size
            pintarPunto(xPosition + i, yPosition + j)
        end
    end
    -- Termina tu código
end

function onClickLeft(down)
    print("Clicked Left")
    if down then
    end
end

function onClickRight(down)
    print("Clicked Right")
    if down then
    end
end


function onMouseMove(posX, posY)
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    print("Key pressed: "..key)
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress, onDraw, window_layer)
mainLoop()

