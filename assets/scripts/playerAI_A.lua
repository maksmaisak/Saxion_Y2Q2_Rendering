--
-- User: maks
-- Date: 2019-01-21
-- Time: 15:36
--

require('assets/scripts/AI')
require('math')

local PlayerAI = AI:new()

local oldStart = PlayerAI.start
function PlayerAI:start()

    oldStart(self)
    self.shootIfReady = coroutine.wrap(function()

        while true do

            while not self:canShoot() do
                coroutine.yield()
            end

            coroutine.yield(self:shoot(self.enemyTransform.position, 10))
        end
    end)
end

function PlayerAI:update(dt)

    for i, bullet in ipairs(Game.bullets) do

        local bulletPosition = bullet:get("Transform").position
        if Vector.distance(bulletPosition, self.steering.position) < 10 then
            self.steering:dodge(bulletPosition, bullet:get("Rigidbody").velocity)
        end
    end

    if not self.enemy.isDestroyed then

        local enemyPosition = self.enemyTransform.position
        if Vector.distance(enemyPosition, self.steering.position) > 10 then
            self.steering:seek(enemyPosition)
        end

        self.shootIfReady()
    end

    if self.steering.steer:magnitude() < 0.001 then
        self.steering:alignVelocity({x = 0, y = 0, z = 0})
    end

    --self.steering:flee(self.enemyTransform.position)

    self:updateSteering(dt)
end

return function(o)
    return PlayerAI:new(o)
end