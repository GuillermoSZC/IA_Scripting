-- Escribe codigo
require "library"
require "prepare"

-- Define tus variables globales
x=0
y=0
-- Termina tu definicion de variables

function pintarPunto(x,y)
    -- Rellenar código para pintar un punto en la pantalla
    drawPoint(x,y)
    -- Fin de código
end

function onUpdate(seconds)

--testeo
x=50
y=50
onDraw()
end

function onDraw()
    -- Empieza tu código, que debe emplear la funcion pintarPunto
    for num=0,50,1 do
        for numy=0,50,1 do
            pintarPunto(x+num,y+numy)
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

