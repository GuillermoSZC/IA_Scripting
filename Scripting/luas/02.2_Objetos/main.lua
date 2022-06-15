-- Escribe codigo
require "library"
require "prepare"

-- Define tus variables globales
enemigo={vida=100, X=100, Y=100, size =10, huir=false}
enemigoHuidizo={vida=100, X=100, Y=100, size=10, huir=true}
-- Termina tu definicion de variables


    -- Rellenar código 
mtEnemy={}

function clicked(enemy)
    enemy.vida=enemy.vida-10
    
    if enemy.huir then
        enemy.X=math.random(1,1000)
        enemy.Y=math.random(1,1000)
    end
    
    if enemy.vida<10 then
        enemy.size=enemy.size/2
    end
end

mtEnemy._add=clicked
setmetatable(enemigo,mtEnemy)
setmetatable(enemigoHuidizo,mtEney)
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
        if mousePos.X==enemigo.X and mousePosY==enemigo.Y then
            enemigo.clicked(enemigo)        
        end
        
        if mousePos.X==enemigoHuidizo.X and mousePosY==enemigoHuidizo.Y then
            enemigoHuidizo.clicked(enemigoHuidizo)        
        end
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

