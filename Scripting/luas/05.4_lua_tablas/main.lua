-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales
creatures = {}
creatures["grunt"] = { image = "creatures/grunt.png", dimX = 64, dimY = 64,sizeX = 64, sizeY = 64}
creatures["mage"] = { image = "creatures/mago.png", dimX = 24, dimY = 24, sizeX = 64,sizeY = 64}
creatures["griphon"] = { image = "creatures/gryphon.png", dimX = 128, dimY = 128, sizeX = 128, sizeY = 128}
creatures["dragon"] = { image = "creatures/dragon.png", dimX = 64, dimY = 64, sizeX = 256, sizeY = 256}
creatures["peon"] = { image = "creatures/peon.png", dimX = 24, dimY = 64, sizeX = 64, sizeY = 64}

mapa = {
    {
        name = "griphon",
        position = { x = 200, y = 100},
    },
    {
        name = "mage",
        position = { x = 100, y = 200},
    },
    {
        name = "mage",
        position = { x = 100, y = 300},
    },
    {
        name = "grunt",
        position = { x = 150, y = 150},
    },        
    {
        name = "grunt",
        position = { x = 150, y = 350},
    },
    {
        name = "peon",
        position = { x = 400, y = 100},
    },
    {
        name = "dragon",
        position = { x = 400, y = 400},
    },
    {
        name = "dragon",
        position = { x = 200, y = 200},
    },
    {
        name = "dragon",
        position = { x = 600, y = 600},
    },
}
-- Fin de tus variables globales

-- Define tus funciones y llamadas
function addCreature(creature_name, posX, posY)
    texture_name = creatures[creature_name].texture
   return addImage(texture_name, posX, posY, creatures[creature_name].sizeX, creatures[creature_name].sizeY)
end

function drawMap(map)
    for iCreature = 1, #mapa do
      addCreature(mapa[iCreature].name, mapa[iCreature].position.x, mapa[iCreature].position.y)
              print("criatura pintada")
    end
        print("mapa dibujado")
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

