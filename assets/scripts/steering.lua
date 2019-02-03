--
-- User: maks
-- Date: 2019-02-01
-- Time: 18:51
--

require('assets/scripts/object')
require('assets/scripts/vector')

Steering = Object:new {
    maxSpeed = 10,
    maxForce = 10,
    maxLookahead = 1
}

function Steering:init()

    self.position = self.position or Vector:new()
    self.velocity = self.velocity or Vector:new()
    self.steer = self.steer or Vector:new()
end

function Steering:update(dt)

    self.velocity:add(self.steer    * dt):truncate(self.maxSpeed)
    self.position:add(self.velocity * dt)

    self.steer:reset()
end

function Steering:seek(position)

    self.steer:add(
        Vector.from(position)
            :sub(self.position):setMagnitude(self.maxSpeed)
            :sub(self.velocity):truncate(self.maxForce)
    )
end

function Steering:flee(position)

    self.steer:add(
        Vector.from(self.position)
            :sub(position):setMagnitude(self.maxSpeed)
            :sub(self.velocity):truncate(self.maxForce)
    )
end

function Steering:alignVelocity(velocity)

    self.steer:add(
        Vector.from(velocity):truncate(self.maxSpeed):sub(self.velocity):truncate(self.maxForce)
    )
end

function Steering:brake()
    self:alignVelocity({0, 0, 0})
end

function Steering:arrive(position, radius)

    radius = radius or 1

    local distance = Vector.distance(position, self.position)
    local desiredVelocity = Vector.from(position)
        :sub(self.position):setMagnitude(self.maxSpeed)

    if (distance < radius) then
        desiredVelocity:mul(distance / radius)
    end

    self:alignVelocity(desiredVelocity)
end

function Steering:dodge(position, velocity)

    local toSide = Vector.from(velocity):normalize():doCross({x = 0, y = 1, z = 0}):normalize()
    local ahead = Vector.from(self.velocity):setMagnitude(self.maxLookahead):add(self.position)
    --local ahead = Vector.from(self.position)
    if Vector.from(ahead):sub(position):dot(toSide) < 0 then
        toSide:mul(-1)
    end

    self:alignVelocity(toSide:setMagnitude(self.maxSpeed))
end
