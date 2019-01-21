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

function AI:shootAt(position)

    print("position: ", position.x, position.y, position.z)

--    local b = Game.makeActor("Bullet")
--    b.addComponent("Transform")
--    b.addComponent("Rigidbody"):setVelocity({1, 0, 0})
--    b.addComponent("RenderInfo", {mesh = "assets/models/sphere2.obj", material = {}})
--    b.addComponent("Light")
end

function AI:update(dt)

    --self.transform:move(0, 0, -dt)
    self.transform.position = {0, 1, 0}
    print(self.transform.position)
    --self:shootAt(self.enemyTransform.position)
end

return function(o)
    return AI:new(o)
end