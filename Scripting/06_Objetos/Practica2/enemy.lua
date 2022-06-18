require "library"

Enemigo = {}
function Enemigo:new(_name)
    local enemy = {}
    setmetatable(enemy, self)
    self.__index = self
    
    if _name ~= nil then
        enemy.name = _name
        enemy.maxLife = 100
        enemy.life = 70
        enemy.dimX = creatures[_name].dimX
        enemy.dimY = creatures[_name].dimY
    end
    
    return enemy
end

function Enemigo:receiveDamage(_damage)
    if self.life > 0 then
        self.life = self.life - _damage
        if self.life == 0 then
            self:dead()
        end
    end
end

EnemigoHuidizo = Enemigo:new()

function EnemigoHuidizo:receiveDamage(_damage)
    Enemigo.receiveDamage(self, _damage)
    if self.life > 0 and self.life < self.maxLife * 0.5 then
        math.randomseed(os.time())
        newX = math.random(1024 - self.dimX)
        newY = math.random(768 - self.dimY)
        removeCreature(self.id)
        self.posX = newX
        self.posY = newY
        self.id = addCreature(self.name, self.posX, self.posY, self.dimX, self.dimY)
    end
end

function Enemigo:dead()
    self.dimX = self.dimX * 0.5
    self.dimY = self.dimY * 0.5
    positionX = self.posX
    positionY = self.posY
    removeCreature(self.id)
    self.id = addCreature(self.name, positionX, positionY, self.dimX, self.dimY)
end



