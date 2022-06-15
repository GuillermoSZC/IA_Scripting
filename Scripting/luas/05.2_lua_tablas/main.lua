-- Escribe codigo
require "library"
prepareWindow()

mousePositionX = nil
mousePositionY = nil

-- Define tus variables globales
creatures = {}
creatures["grunt"] = { image = "creatures/grunt.png", dimX = 64, dimY = 64}
creatures["mage"] = { image = "creatures/mago.png", dimX = 24, dimY = 24}
creatures["griphon"] = { image = "creatures/gryphon.png", dimX = 128, dimY = 128}
creatures["dragon"] = { image = "creatures/dragon.png", dimX = 64, dimY = 64}

-- Fin de tus variables globales

-- Define tus funciones y llamadas
function drawCreature(layer, creature_name, positionX, positionY)
    posX = positionX or 0
    posY = positionY or 0
    gfxQuad = MOAIGfxQuad2D.new()
    
    texture_name = creatures[creature_name].image
  
    gfxQuad:setTexture(texture_name)
    gfxQuad:setRect(0, 0, creatures[creature_name].dimX, creatures[creature_name].dimY)
    gfxQuad:setUVRect(0, 0, 1, 1)
  
    prop = MOAIProp2D.new()
    prop:setDeck(gfxQuad)
    prop:setLoc(posX, posY)
    layer:insertProp(prop)
    return prop
end
-- Fin de tus funciones

addCreature("dragon",500,500)


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

