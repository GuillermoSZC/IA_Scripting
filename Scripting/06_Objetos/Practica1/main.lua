-- Escribe codigo
require "library"
require "prepare"
require "vector"

-- vector comprobations
vec = new(5, 5)
vec2 = new(3, 2)
print(vec)
print(vec2)

vecsum = vec + vec2
print(vecsum)

vecrest = vec - vec2
print(vecrest)

vecdot = vec:dot(vec2)
print(vecdot)

veclength = vec:len()
print(veclength)

vecnorm = vec:normalize()
print(vecnorm)

vecmul = vec:mul(2)
print(vecmul)



function onUpdate(seconds)
    
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

