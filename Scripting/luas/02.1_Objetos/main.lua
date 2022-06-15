-- Escribe codigo
require "library"
require "prepare"

-- Define tus variables globales
vector={}
-- Termina tu definicion de variables


    -- Rellenar código 
mtVector={}

function sumar(vector1,vector2)
    return vector={x=vector1.x+vector2.x,y=vector1.y+vector2.y}
end

function restar(vector1,vector2)
    return vector={x=vector1.x-vector2.x,y=vector1.y-vector2.y}
end

function dot (vector1,vector2)
    return  (vector1.x * vector2.x) + (vector1.y * vector2.y);
end

function length (vector)
    return math.sqrt((vector.x) ^ 2 + (vector.y) ^ 2)
end

function normalize (vector)
    len=math.sqrt((vector.x) ^ 2 + (vector.y) ^ 2)
    vec={x=vector.x/len,y=vector.y/len}
    return vec
end

function scalar (vector, num)
    len=math.sqrt((vector.x) ^ 2 + (vector.y) ^ 2)
    vec={x=vector.x/len*num,y=vector.y/len*num}
    return vec
end

function printer (vector)
    print(vec)
end

vector._add=sumar
vector._add=restar
vector._add=dot
vector._add=normalize
vector._add=scalar
vector._add=printer
vector._add=length
    -- Fin de código

function onUpdate(seconds)

--testeo
x=50
y=50
onDraw()
end

function onDraw()
    -- Empieza tu código

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

