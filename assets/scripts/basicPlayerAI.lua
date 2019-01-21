--
-- User: maks
-- Date: 2019-01-21
-- Time: 15:36
--

require("./assets/scripts/object")

AI = Object:new()

function AI:start()

    self.transform = self.actor:getComponent("Transform")
    self.enemyTransform = self.enemy:getComponent("Transform")
end

function AI:update(dt)

    self.transform:move(0, 0, -dt)
end

return function(o)
    return AI:new(o)
end