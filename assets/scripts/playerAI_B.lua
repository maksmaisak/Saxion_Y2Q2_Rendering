--
-- User: maks
-- Date: 2019-01-21
-- Time: 22:54
--

require('assets/scripts/steering')

return function(o)

    o = o or {}

    local transform
    local rigidbody
    local steering = Steering:new {
        maxSpeed = 10,
        maxForce = 1000
    }

    function o:start()
        transform = self.actor:get("Transform")
        rigidbody = self.actor:get("Rigidbody")
    end

    function o:update(dt)

        steering.position:set(transform.position)
        steering.velocity:set(rigidbody.velocity)

        for i, bullet in ipairs(Game.bullets) do

            local bulletPosition = bullet:get("Transform").position
            if Vector.distance(bulletPosition, steering.position) < 10 then
                steering:dodge(bulletPosition, bullet:get("Rigidbody").velocity)
            end
        end

        if (steering.steer:magnitude() < 0.001) then
            steering:alignVelocity({x = 0, y = 0, z = 0})
        end

        steering:update(dt)
        rigidbody.velocity = steering.velocity
    end

    return o
end