--
-- User: maks
-- Date: 2019-01-21
-- Time: 15:36
--

require('assets/scripts/AI')
require('math')

-- How many seconds away a bullet must be from hitting you to be dodged
local minTimeBeforeBulletHit = 0.2

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

    local movers = {}
    for i, bullet in ipairs(Game.bullets) do

        movers[i] = {
            position = bullet:get("Transform").position,
            velocity = bullet:get("Rigidbody").velocity
        }
    end
    self.steering:avoidMovingObjects(movers, minTimeBeforeBulletHit)

    if not self.enemy.isDestroyed then
        self.shootIfReady()
    end

    if self.steering.steer:magnitude() < 0.001 then

        local enemyPosition = not self.enemy.isDestroyed and self.enemy:get("Transform").position
        if enemyPosition and Vector.distance(self.transform.position, enemyPosition) > 20 then
            self.steering:seek(enemyPosition)
        else
            self.steering:alignVelocity({x = 0, y = 0, z = 0})
        end
    end

    --self.steering:flee(self.enemyTransform.position)

    self:updateSteering(dt)
end

return function(o)
    return PlayerAI:new(o)
end