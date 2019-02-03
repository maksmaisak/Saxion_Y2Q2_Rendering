--
-- User: maks
-- Date: 2019-02-02
-- Time: 17:45
--

require('assets/scripts/object')
require('assets/scripts/vector')
require('assets/scripts/steering')

AI = Object:new {
    shootCooldown = 2,
    bulletSpeed = 20
}

function AI:start()

    self.steering = Steering:new()
    self.transform = self.actor:get("Transform")
    self.rigidbody = self.actor:get("Rigidbody")
    self.enemyTransform = self.enemy:get("Transform")

    self.steering.position:set(self.transform.position)
    self.steering.velocity:set(self.rigidbody.velocity)

    self.timeToShoot = Game.getTime()
    function self:canShoot() return Game.getTime() >= self.timeToShoot end
    function self:shoot(targetPosition)

        if not self:canShoot() then
            return nil
        end
        self.timeToShoot = Game.getTime() + self.shootCooldown

        local spawnAheadDistance = 2
        local startPosition = Vector.from(self.transform.position)

        local direction = Vector.from(targetPosition):sub(startPosition):normalize()
        local velocity = direction * self.bulletSpeed;
        startPosition:add(direction * spawnAheadDistance)
        --print("velocity: ", velocity.x, velocity.y, velocity.z)

        return Game.makeBullet(startPosition, velocity)
    end
end

function AI:updateSteering(dt)

    self.steering:update(dt)
    self.rigidbody.velocity = self.steering.velocity

    self.steering.position:set(self.transform.position)
    self.steering.velocity:set(self.rigidbody.velocity)
end
