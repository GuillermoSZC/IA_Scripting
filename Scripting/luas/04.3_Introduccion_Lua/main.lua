-- Escribe codigo
require "library"
prepareWindow()

carta, carta_image = drawImage(layer, "cards\\A_C.png", 256, 256, 79, 123)
mousePositionX = 0
mousePositionY = 0

    -- Escribe tu código
    palo="b"
    numero="1"
    -- Termina tu código

function onUpdate(seconds)
end

function onClickLeft(down)
    if down then
        print("Clicked Left")
    end
end

function onClickRight(down)
    print("Clicked Right")
end

function onMouseMove(posX, posY)
    mousePositionX = posX
    mousePositionY = posY
    --print("Mouse Moved to " .. posX .. ","..posY)
end

function onKeyPress(key, down)
    image_file = nil
    key_pressed = convertKeyToChar(key)
    print("Key pressed: ", key_pressed)
    
-- Escribe tu código para gestion de teclado
if down then
    if key_pressed=="c" or key_pressed=="C" then
        palo="C"
    elseif key_pressed=="d" or key_pressed=="D" then
        palo="D"
    elseif key_pressed=="t" or key_pressed=="T" then
        palo="T"
    elseif key_pressed=="p" or key_pressed=="P" then
        palo="P"
            elseif key_pressed=="2" then
        numero="2"
            elseif key_pressed=="3" then
        numero="3"
            elseif key_pressed=="4" then
        numero="4"
            elseif key_pressed=="5" then
        numero="5"
            elseif key_pressed=="6" then
        numero="6"
            elseif key_pressed=="7" then
        numero="7"
            elseif key_pressed=="8" then
        numero="8"
            elseif key_pressed=="9" then
        numero="9"
            elseif key_pressed=="j" or key_pressed=="J" then
        numero="J"
            elseif key_pressed=="q" or key_pressed=="Q" then
        numero="Q"
            elseif key_pressed=="k" or key_pressed=="K" then
        numero="K"
    end
else
    palo="b"
    numero ="1"
end


if palo~="b" and numero ~="1" then
    image_file="cards/"..numero.."_"..palo..".png" 
else
    image_file=nil    
end
    
    -- Termina tu código
    
    if image_file then
        setImage(carta_image, image_file)
    end
end



callbackConfiguration(onClickLeft, onClickRight, onMouseMove, onKeyPress)
mainLoop()

