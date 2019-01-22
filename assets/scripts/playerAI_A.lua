--
-- User: maks
-- Date: 2019-01-21
-- Time: 15:36
--

require("./assets/scripts/object")
require("math")

AI = Object:new()

function AI:start()

    self.transform = self.actor:getComponent("Transform")
    self.enemyTransform = self.enemy:getComponent("Transform")

    self:shootAt(self.enemyTransform.position)
end

function AI:shootAt(position)

    print("position: ", position.x, position.y, position.z)

    return Game.makeActor("Bullet", {
        Transform = {
            position = position
        },
        Rigidbody = {
            isKinematic = true,
            useGravity = false,
            velocity = {1, 0, 0}
        },
        RenderInfo = {
            mesh = "models/sphere2.obj",
            material = {shininess = 256}
        },
        Light = {
            intensity = 20
        }
    });
end

function AI:update(dt)

    local time = Game.getTime()
    self.transform.position = {math.cos(time) * 5, 0, math.sin(time * 2) * 5}
end

return function(o)
    return AI:new(o)
end