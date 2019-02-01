--
-- User: maks
-- Date: 2019-01-21
-- Time: 15:36
--

require('assets/scripts/object')
require('assets/scripts/steering')
require('math')

AI = Object:new {
    maxNumActiveBullets = 5
}

function AI:start()

    self.steering = Steering:new()
    self.transform = self.actor:get("Transform")
    self.rigidbody = self.actor:get("Rigidbody")
    self.enemyTransform = self.enemy:get("Transform")
    self.bullets = {}

    self.shootIfReady = coroutine.wrap(function()

        while true do

            self:shoot(self.enemyTransform.position, 10)

            local timeToShoot = Game.getTime() + 2
            while Game.getTime() < timeToShoot do
                coroutine.yield()
            end
        end
    end)
end

function AI:shoot(targetPosition, speed)

    speed = speed or 10
    local spawnAheadDistance = 2
    local startPosition = Vector.from(self.transform.position)

    local direction = Vector.from(targetPosition):sub(startPosition):normalize()
    local velocity = direction * speed;
    startPosition:add(direction * spawnAheadDistance)
    --print("velocity: ", velocity.x, velocity.y, velocity.z)

    return Game.makeBullet(startPosition, velocity)
end

function AI:update(dt)

    self.steering.position:set(self.transform.position)
    self.steering.velocity:set(self.rigidbody.velocity)

    for i, bullet in ipairs(Game.bullets) do

        local bulletPosition = bullet:get("Transform").position
        if Vector.distance(bulletPosition, self.steering.position) < 10 then
            self.steering:dodge(bulletPosition, bullet:get("Rigidbody").velocity)
        end
    end

    if (self.steering.steer:magnitude() < 0.001) then
        self.steering:alignVelocity({x = 0, y = 0, z = 0})
    end

    --self.steering:flee(self.enemyTransform.position)
    self.shootIfReady()
    --print("bullet position: ", bulletPos.x, bulletPos.y, bulletPos.z)

    self.steering:update(dt)
    self.rigidbody.velocity = self.steering.velocity
    --self.transform.position = self.steering.position
end

return function(o)
    return AI:new(o)
end