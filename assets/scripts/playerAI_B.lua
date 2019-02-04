--
-- User: maks
-- Date: 2019-01-21
-- Time: 22:54
--

require('math')
require('assets/scripts/AI')

return function(o)

    o = AI:new(o)

    function o:update(dt)

        -- dodge bullets
        for i, bullet in ipairs(Game.bullets) do

            local bulletPosition = bullet:get("Transform").position
            if Vector.distance(bulletPosition, self.steering.position) < 10 then
                self.steering:dodge(bulletPosition, bullet:get("Rigidbody").velocity)
            end
        end

        if (not self.enemy.isDestroyed) then

            -- move away from the enemy if too close
            local enemyPosition = self.enemyTransform.position
            if Vector.distance(enemyPosition, self.steering.position) < 10 then
                --self.steering:flee(enemyPosition)
            end

            if (self:canShoot()) then
                self:shoot(self.enemyTransform.position)
                self.timeToShoot = self.timeToShoot + math.random(-1, 1)
            end
        end

        if (self.steering.steer:magnitude() < 0.001) then
            self.steering:alignVelocity({x = 0, y = 0, z = 0})
        end

        self:updateSteering(dt)
    end

    return o
end