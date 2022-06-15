-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales
creatures = {}
creatures["Grifo"] = { image = "creatures/gryphon.png", dimX = 128, dimY = 128}
creatures["Mago"] = { image = "creatures/mage.png", dimX = 64, dimY = 64}
creatures["Grunt"] = { image = "creatures/grunt.png", dimX = 64, dimY = 64}
creatures["Peon"] = { image = "creatures/peon.png", dimX = 64, dimY = 64}
creatures["Dragon"] = { image = "creatures/dragon.png", dimX = 64, dimY = 64}
}

mapa = {
    {
        name = "Grifo",
        position = { x = 200, y = 100},
    },
    {
        name = "Mago",
        position = { x = 100, y = 200},
    },
    {
        name = "Peon",
        position = { x = 400, y = 100},
    },
    {
        name = "Dragon",
        position = { x = 400, y = 400},
    },
    {
        name = "Grunt",
        position = { x = 900, y = 650 },
    },
}
    
-- Fin de tus variables globales

-- Define tus funciones y llamadas
function addCreature(creature_name, posX, posY)
    texture_name = criaturas[creature_name].texture
    addImage(texture_name, posX, posY, criaturas[creature_name].size.x, criaturas[creature_name].size.y)
end

function drawMap(map)
    for iCreature = 1, #mapa do
        addCreature(mapa[iCreature].name, mapa[iCreature].position.x, mapa[iCreature].position.y)
    end
end

drawMap(mapa)

-- Fin de tus funciones

function onUpdate(seconds)
end

function onClickLeft(down)
    print("Clicked Left")
    if not down then
        -- Escribe tu código para el botón izquierdo
        -- Termina tu código
    end
end

function onClickRight(down)
    print("Clicked Right")
    if not down then
        -- Escribe tu código para el botón derecho
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

